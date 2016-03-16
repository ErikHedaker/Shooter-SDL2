#include "Game.h"
#include "Enums.h"
#include "Functions.h"
#include <SDL.h>
#include <iostream>
#include <map>
#include <math.h>
#include <algorithm>
#include <functional>

Trait::Trait( ) :
    type( Representation::None )
{ }
Trait::Trait( const Representation& type, int value ) :
    type( type )
{
    INT = value;
}
Trait::Trait( const Representation& type, double value ) :
    type( type )
{
    DOUBLE = value;
}
Trait::Trait( const Representation& type, Projectile value ) :
    type( type )
{
    PROJECTILE = value;
}

std::size_t Components::Add( )
{
    indexCount++;
    name.emplace_back( );
    texture.emplace_back( );
    size.emplace_back( );
    position.emplace_back( );
    velocityLimit.emplace_back( );
    velocity.emplace_back( );
    acceleration.emplace_back( );
    trait.emplace_back( );
    attributes.emplace_back( );
    states.emplace_back( );

    return indexCount - 1;
}
void Components::Delete( std::size_t index )
{
    const std::size_t indexLast = indexCount - 1;

    std::swap( name[index], name[indexLast] );
    std::swap( texture[index], texture[indexLast] );
    std::swap( size[index], size[indexLast] );
    std::swap( position[index], position[indexLast] );
    std::swap( velocityLimit[index], velocityLimit[indexLast] );
    std::swap( velocity[index], velocity[indexLast] );
    std::swap( acceleration[index], acceleration[indexLast] );
    std::swap( trait[index], trait[indexLast] );
    std::swap( attributes[index], attributes[indexLast] );
    std::swap( states[index], states[indexLast] );

    indexCount--;
    name.pop_back( );
    texture.pop_back( );
    size.pop_back( );
    position.pop_back( );
    velocityLimit.pop_back( );
    velocity.pop_back( );
    acceleration.pop_back( );
    trait.pop_back( );
    attributes.pop_back( );
    states.pop_back( );
}

Game::Game( const std::string& name, const Vector2<double>& screenSize ) :
    _name( name ),
    _screenSize( screenSize ),
    _libraryProjectiles
    ( {
        { Projectiles::None,       {  0,    0.0,    0.0,  0.0, 0.0 } },
        { Projectiles::Pistol,     {  1, 2000.0, 2000.0, 0.35, 0.0 } },
        { Projectiles::Shotgun,    { 12, 2000.0, 2000.0, 0.75, 3.5 } },
        { Projectiles::Machinegun, {  1, 2000.0, 2000.0, 0.05, 3.0 } },
        { Projectiles::Framegun,   {  1, 2000.0, 2000.0, 0.00, 1.5 } }
    } ),
    _timePrevious( 0 ),
    _timeCurrent( 0 ),
    _timeStep( 0 ),
    _timeScale( 1.0 )
{
    try
    {
        if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
        {
            throw std::exception( SDL_GetError( ) );
        }

        _window = SDL_CreateWindow( name.c_str( ), 100, 100, static_cast<int>( _screenSize.x ), static_cast<int>( _screenSize.y ), SDL_WINDOW_SHOWN );

        if( _window == nullptr )
        {
            throw std::exception( SDL_GetError( ) );
        }

        _renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

        if( _renderer == nullptr )
        {
            throw std::exception( SDL_GetError( ) );
        }
    }
    catch( const std::exception& e )
    {
        std::cout << "Exception: " << e.what( );
        std::cout << "\nPress enter to exit: ";
        std::cin.get( );
        exit( 0 );
    }

    /* Test entities */
    std::size_t index = _components.Add( );

    _indexPlayer = index;
    _components.name[index] = "Player";
    _components.size[index] = { 30.0, 30.0 };
    _components.position[index] = { _screenSize.x / 2.0, 0 };
    _components.velocityLimit[index] = { 1000.0, 5000.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.trait[index].emplace_back( Representation::Projectile, _libraryProjectiles.at( Projectiles::Pistol ) );
    _components.attributes[index] = Attributes::Renderable | Attributes::Collide | Attributes::Collision | Attributes::Friction | Attributes::Gravity;
    _components.states[index] = 0;
    _components.texture[index] = LoadTexture( "empty.bmp", _renderer );
    SDL_SetTextureColorMod( _components.texture[index], 255, 0, 0 );

    index = _components.Add( );
    _components.name[index] = "Ground";
    _components.size[index] = { _screenSize.x * 3.0, 100.0 };
    _components.position[index] = { -_screenSize.x, _screenSize.y - 50.0 };
    _components.velocityLimit[index] = { 0.0, 0.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.attributes[index] = Attributes::Renderable | Attributes::Collide | Attributes::Collision;
    _components.states[index] = 0;
    _components.texture[index] = LoadTexture( "empty.bmp", _renderer );

    index = _components.Add( );
    _components.name[index] = "Wall Left";
    _components.size[index] = { 100.0, _screenSize.y * 3.0 };
    _components.position[index] = { -_screenSize.x - 100.0, -_screenSize.y * 2.0 + 50.0 };
    _components.velocityLimit[index] = { 0.0, 0.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.attributes[index] = Attributes::Renderable | Attributes::Collide | Attributes::Collision;
    _components.states[index] = 0;
    _components.texture[index] = LoadTexture( "empty.bmp", _renderer );

    index = _components.Add( );
    _components.name[index] = "Wall Right";
    _components.size[index] = { 100.0, _screenSize.y * 3.0 };
    _components.position[index] = { _screenSize.x * 2.0, -_screenSize.y * 2.0 + 50.0 };
    _components.velocityLimit[index] = { 0.0, 0.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.attributes[index] = Attributes::Renderable | Attributes::Collide | Attributes::Collision;
    _components.states[index] = 0;
    _components.texture[index] = LoadTexture( "empty.bmp", _renderer );

    index = _components.Add( );
    _components.name[index] = "Platform Bottom Left";
    _components.size[index] = { _screenSize.x, 100.0 };
    _components.position[index] = { -_screenSize.x + 300.0, _screenSize.y - 300.0 };
    _components.velocityLimit[index] = { 0.0, 0.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.attributes[index] = Attributes::Renderable | Attributes::Collide | Attributes::Collision;
    _components.states[index] = 0;
    _components.texture[index] = LoadTexture( "empty.bmp", _renderer );

    index = _components.Add( );
    _components.name[index] = "Platform Bottom Right";
    _components.size[index] = { _screenSize.x, 100.0 };
    _components.position[index] = { _screenSize.x - 300.0, _screenSize.y - 300.0 };
    _components.velocityLimit[index] = { 0.0, 0.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.attributes[index] = Attributes::Renderable | Attributes::Collide | Attributes::Collision;
    _components.states[index] = 0;
    _components.texture[index] = LoadTexture( "empty.bmp", _renderer );

    index = _components.Add( );
    _components.name[index] = "Platform Top Left";
    _components.size[index] = { _screenSize.x, 100.0 };
    _components.position[index] = { -_screenSize.x + 300.0, _screenSize.y - 550.0 };
    _components.velocityLimit[index] = { 0.0, 0.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.attributes[index] = Attributes::Renderable | Attributes::Collide | Attributes::Collision;
    _components.states[index] = 0;
    _components.texture[index] = LoadTexture( "empty.bmp", _renderer );

    index = _components.Add( );
    _components.name[index] = "Platform Top Right";
    _components.size[index] = { _screenSize.x, 100.0 };
    _components.position[index] = { _screenSize.x - 300.0, _screenSize.y - 550.0 };
    _components.velocityLimit[index] = { 0.0, 0.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.attributes[index] = Attributes::Renderable | Attributes::Collide | Attributes::Collision;
    _components.states[index] = 0;
    _components.texture[index] = LoadTexture( "empty.bmp", _renderer );

    index = _components.Add( );
    _components.name[index] = "Box";
    _components.size[index] = { 75.0, 75.0 };
    _components.position[index] = _screenSize / 2.0;
    _components.velocityLimit[index] = { 1000.0, 1000.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.attributes[index] = Attributes::Renderable | Attributes::Collide | Attributes::Collision | Attributes::Gravity;
    _components.states[index] = 0;
    _components.texture[index] = LoadTexture( "empty.bmp", _renderer );
}
Game::~Game( )
{
    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        if( _components.attributes[index] & Attributes::Renderable )
        {
            SDL_DestroyTexture( _components.texture[index] );
        }
    }

    SDL_DestroyRenderer( _renderer );
    SDL_DestroyWindow( _window );
    SDL_Quit( );
}

void Game::Start( )
{
    while( true )
    {
        UpdateTime( );
        ProcessInput( );
        UpdateEntities( );
        Draw( );
    }
}

void Game::CreateProjectile( const Vector2<double>& origin, const Vector2<double>& mouse, const Projectile& projectile )
{
    static double previous = 0;

    if( previous + projectile.delay / _timeScale < _timeCurrent )
    {
        previous = _timeCurrent;
        
        for( int i = 0; i < projectile.amount; i++ )
        {
            const double accuracy = 35.0;
            Vector2<double> normal = NormalizeVector( mouse - origin ) * accuracy;
            Vector2<double> direction;
            Vector2<double> position;
            std::size_t index;

            if( ( normal.x > 0 && normal.y > 0 ) ||
                ( normal.x < 0 && normal.y < 0 ) )
            {
                normal.x += RandomNumberGenerator( -projectile.spread, projectile.spread );
                normal.y -= RandomNumberGenerator( -projectile.spread, projectile.spread );
            }
            else
            {
                normal.x += RandomNumberGenerator( -projectile.spread, projectile.spread );
                normal.y += RandomNumberGenerator( -projectile.spread, projectile.spread );
            }

            if( normal.x <  1.0 &&
                normal.x > -1.0 )
            {
                normal.x = 1.0 * ( normal.x < 0 ? -1.0 : 1.0 );
            }

            if( normal.y <  1.0 &&
                normal.y > -1.0 )
            {
                normal.y = 1.0 * ( normal.y < 0 ? -1.0 : 1.0 );
            }

            position = origin + normal;
            direction = NormalizeVector( position - origin );

            index = _components.Add( );
            _components.name[index] = "Projectile";
            _components.size[index] = { 3.0, 3.0 };
            _components.position[index] = position - _components.size[index] / 2.0;
            _components.velocityLimit[index] = { 10000, 10000 };
            _components.velocity[index] = direction * projectile.velocity;
            _components.acceleration[index] = direction * projectile.acceleration;
            _components.trait[index].emplace_back( Representation::Lifetime, 1.0 );
            _components.attributes[index] = Attributes::Renderable | Attributes::Deletable | Attributes::Collide;
            _components.states[index] = 0;
            _components.texture[index] = LoadTexture( "empty.bmp", _renderer );
            SDL_SetTextureColorMod( _components.texture[index], 0, 255, 255 );
        }
    }
}
void Game::UpdateTime( )
{
    _timePrevious = _timeCurrent;
    _timeCurrent = static_cast<double>( SDL_GetTicks( ) ) / 1000.0;
    _timeStep = ( _timeCurrent - _timePrevious ) * _timeScale;
}
void Game::ProcessInput( )
{
    static const std::map<int, int> inputPlayer =
    {
        { SDLK_1, Projectiles::Pistol     },
        { SDLK_2, Projectiles::Shotgun    },
        { SDLK_3, Projectiles::Machinegun },
        { SDLK_4, Projectiles::Framegun   }
    };

    while( SDL_PollEvent( &_event ) )
    {
        switch( _event.type )
        {
            case SDL_KEYDOWN:
            {
                switch( _event.key.keysym.sym )
                {
                    case SDLK_1:
                    case SDLK_2:
                    case SDLK_3:
                    case SDLK_4:
                    {
                        for( auto& trait : _components.trait[_indexPlayer] )
                        {
                            if( trait.type == Representation::Projectile )
                            {
                                trait.PROJECTILE = _libraryProjectiles.at( inputPlayer.at( _event.key.keysym.sym ) );
                            }
                        }

                        break;
                    }
                    case SDLK_ESCAPE:
                    {
                        exit( 0 );
                    }
                    default:
                    {
                        break;
                    }
                }

                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                switch( _event.button.button )
                {
                    case SDL_BUTTON_LEFT:
                    {
                        _mouseButtonLeft = true;

                        break;
                    }
                    case SDL_BUTTON_RIGHT:
                    {
                        _mouseButtonRight = true;

                        break;
                    }
                    default:
                    {
                        break;
                    }
                }

                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                switch( _event.button.button )
                {
                    case SDL_BUTTON_LEFT:
                    {
                        _mouseButtonLeft = false;

                        break;
                    }
                    case SDL_BUTTON_RIGHT:
                    {
                        _mouseButtonRight = false;

                        break;
                    }
                    default:
                    {
                        break;
                    }
                }

                break;
            }
            case SDL_QUIT:
            {
                exit( 0 );
            }
            default:
            {
                break;
            }
        }
    }

    if( _mouseButtonLeft )
    {
        const Vector2<double> start = _components.position[_indexPlayer] + _components.size[_indexPlayer] / 2.0;
        Projectile projectile;
        int x;
        int y;

        for( auto& trait : _components.trait[_indexPlayer] )
        {
            if( trait.type == Representation::Projectile )
            {
                projectile = trait.PROJECTILE;
            }
        }

        SDL_GetMouseState( &x, &y );
        CreateProjectile( start, { static_cast<double>( x ), static_cast<double>( y ) }, projectile );
    }

    if( _mouseButtonRight )
    {
        _timeScale = 0.2;
    }
    else
    {
        _timeScale = 1.0;
    }

    const Uint8* keyState = SDL_GetKeyboardState( nullptr );
    const double playerAcceleration = 10000.0;
    const double jumpVelocity = 2250.0;

    if( keyState[SDL_SCANCODE_SPACE] &&
        !( _components.states[_indexPlayer] & States::Falling ) )
    {
        _components.velocity[_indexPlayer].y = -jumpVelocity;
    }

    if( keyState[SDL_SCANCODE_A] )
    {
        _components.acceleration[_indexPlayer].x = -playerAcceleration;
    }
    else if( keyState[SDL_SCANCODE_D] )
    {
        _components.acceleration[_indexPlayer].x = playerAcceleration;
    }
    else
    {
        _components.acceleration[_indexPlayer].x = 0.0;
    }
}
void Game::UpdateEntities( )
{
    UpdateVelocity( );
    ApplyFriction( );
    ApplyGravity( );
    ApplyVelocityLimit( );
    UpdatePosition( );
    HandleCollision( );
    HandleLifetime( );
    HandleOutOfBounds( );
    DeleteEntities( );
}
void Game::Draw( )
{
    SDL_RenderClear( _renderer );

    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        if( _components.attributes[index] & Attributes::Renderable )
        {
            SDL_Rect destinationRect;

            destinationRect.x = static_cast<int>( _components.position[index].x );
            destinationRect.y = static_cast<int>( _components.position[index].y );
            destinationRect.w = static_cast<int>( _components.size[index].x );
            destinationRect.h = static_cast<int>( _components.size[index].y );

            SDL_RenderCopy( _renderer, _components.texture[index], nullptr, &destinationRect );
        }
    }

    SDL_RenderPresent( _renderer );
}

void Game::UpdateVelocity( )
{
    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        _components.velocity[index] += _components.acceleration[index] * _timeStep;
    }
}
void Game::ApplyFriction( )
{
    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        if( _components.attributes[index] & Attributes::Friction )
        {
            const double friction = 4500.0 * _timeStep;

            if( _components.velocity[index].x <  friction / 2.0 &&
                _components.velocity[index].x > -friction / 2.0 )
            {
                _components.velocity[index].x = 0.0;
            }
            else
            {
                _components.velocity[index].x += _components.velocity[index].x > 0 ? -friction : friction;
            }
        }
    }
}
void Game::ApplyGravity( )
{
    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        if( _components.attributes[index] & Attributes::Gravity &&
            _components.states[index] & States::Falling )
        {
            const double gravity = 7500.0 * _timeStep;

            _components.velocity[index].y += gravity;
        }
    }
}
void Game::ApplyVelocityLimit( )
{
    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        _components.velocity[index].x = Clip( _components.velocity[index].x, -_components.velocityLimit[index].x, _components.velocityLimit[index].x );
        _components.velocity[index].y = Clip( _components.velocity[index].y, -_components.velocityLimit[index].y, _components.velocityLimit[index].y );
    }
}
void Game::UpdatePosition( )
{
    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        _components.position[index] += _components.velocity[index] * _timeStep;
    }
}
void Game::HandleCollision( )
{
    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        _components.states[index] |= States::Falling;

        if( _components.attributes[index] & Attributes::Collide )
        {
            for( std::size_t indexCollision = 0; indexCollision < _components.indexCount; indexCollision++ )
            {
                if( index != indexCollision &&
                    _components.attributes[indexCollision] & Attributes::Collision )
                {
                    if( Collision( _components.position[index], _components.size[index], _components.position[indexCollision], _components.size[indexCollision] ) )
                    {
                        if( _components.velocity[index].x != 0.0 ||
                            _components.velocity[index].y != 0.0 )
                        {
                            _components.position[index] = OffsetCollision( _components.position[index], _components.size[index], _components.velocity[index], _components.position[indexCollision], _components.size[indexCollision] );
                            _components.velocity[index] = { 0.0, 0.0 };
                            _components.acceleration[index] = { 0.0, 0.0 };
                        }
                    }

                    if( _components.attributes[index] & Attributes::Gravity )
                    {
                        Vector2<double> positionBelow = { _components.position[index].x, _components.position[index].y + _components.size[index].y + 1 };
                        Vector2<double> sizeBelow     = { _components.size[index].x, 0 };

                        if( Collision( positionBelow, sizeBelow, _components.position[indexCollision], _components.size[indexCollision] ) )
                        {
                            _components.states[index] &= ~States::Falling;
                        }
                    }
                }
            }
        }
    }
}
void Game::HandleLifetime( )
{
    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        for( auto& trait : _components.trait[index] )
        {
            if( trait.type == Representation::Lifetime )
            {
                trait.DOUBLE -= _timeStep;

                if( trait.DOUBLE < 0 )
                {
                    _indexesDelete.push_back( index );
                }
            }
        }
    }
}
void Game::HandleOutOfBounds( )
{
    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        if( OutOfBounds( _components.position[index] + _screenSize / 2.0, _screenSize * 10.0 ) )
        {
            if( _components.attributes[index] & Attributes::Deletable )
            {
                _indexesDelete.push_back( index );
            }
            else
            {
                _components.velocity[index] = { 0.0, 0.0 };
                _components.position[index] = _screenSize / 2.0;
            }
        }
    }
}
void Game::DeleteEntities( )
{
    std::sort( _indexesDelete.begin( ), _indexesDelete.end( ), std::greater<std::size_t>( ) );

    for( auto index : _indexesDelete )
    {   
        SDL_DestroyTexture( _components.texture[index] );
        _components.Delete( index );
    }

    _indexesDelete.clear( );
}