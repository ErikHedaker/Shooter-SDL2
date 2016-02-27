#include "Game.h"
#include "Enums.h"
#include "Functions.h"
#include <SDL.h>
#include <iostream>
#include <map>
#include <math.h>
#include <algorithm>
#include <functional>

std::size_t Components::Add( )
{
    indexCount++;
    name.emplace_back( );
    texture.emplace_back( );
    size.emplace_back( );
    position.emplace_back( );
    life.emplace_back( );
    velocity.emplace_back( );
    acceleration.emplace_back( );
    velocityLimit.emplace_back( );
    attributes.emplace_back( );
    states.emplace_back( );
    guns.emplace_back( );

    return indexCount - 1;
}
void Components::Delete( std::size_t index )
{
    const std::size_t indexLast = indexCount - 1;

    std::swap( name[index], name[indexLast] );
    std::swap( texture[index], texture[indexLast] );
    std::swap( size[index], size[indexLast] );
    std::swap( position[index], position[indexLast] );
    std::swap( life[index], life[indexLast] );
    std::swap( velocity[index], velocity[indexLast] );
    std::swap( acceleration[index], acceleration[indexLast] );
    std::swap( velocityLimit[index], velocityLimit[indexLast] );
    std::swap( attributes[index], attributes[indexLast] );
    std::swap( states[index], states[indexLast] );
    std::swap( guns[index], guns[indexLast] );

    indexCount--;
    name.pop_back( );
    texture.pop_back( );
    size.pop_back( );
    position.pop_back( );
    life.pop_back( );
    velocity.pop_back( );
    acceleration.pop_back( );
    velocityLimit.pop_back( );
    attributes.pop_back( );
    states.pop_back( );
    guns.pop_back( );
}

Game::Game( const std::string& name, const std::string& resourcesPath, const Vector2<int>& screenSize ) :
    _name( name ),
    _resourcesPath( resourcesPath ),
    _screenSize( screenSize ),
    _libraryGuns
    ( {
        { Guns::Pistol,     { "Pistol",     1, 4000.0, 4000.0, 0.5,  0.0   } },
        { Guns::Shotgun,    { "Shotgun",   12, 4000.0, 4000.0, 0.5,  75.0  } },
        { Guns::Machinegun, { "Machinegun", 1, 4000.0, 4000.0, 0.05, 75.0  } }
    } ),
    _timePrevious( 0 ),
    _timeCurrent( 0 ),
    _timeStep( 0 )
{
    try
    {
        if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
        {
            throw std::exception( SDL_GetError( ) );
        }

        _window = SDL_CreateWindow( name.c_str( ), 100, 100, _screenSize.x, _screenSize.y, SDL_WINDOW_SHOWN );

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
    _components.size[index] = { 50, 50 };
    _components.position[index] = _screenSize / 2;
    _components.velocityLimit[index] = { 1000.0, 5000.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.life[index] = 0;
    _components.attributes[index] = Attributes::Renderable | Attributes::Collision | Attributes::Collide | Attributes::Friction | Attributes::Gravity | Attributes::VelocityLimit;
    _components.states[index] = States::Falling;
    _components.guns[index] = Guns::Machinegun;
    _components.texture[index] = LoadTexture( _resourcesPath + "white.bmp", _renderer );

    index = _components.Add( );
    _components.name[index] = "Ground";
    _components.size[index] = { _screenSize.x, 50 };
    _components.position[index] = { 0, _screenSize.y - 50 };
    _components.velocityLimit[index] = { 0.0, 0.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.life[index] = 0;
    _components.attributes[index] = Attributes::Renderable | Attributes::Collision | Attributes::Collide;
    _components.states[index] = 0;
    _components.texture[index] = LoadTexture( _resourcesPath + "grass.bmp", _renderer );

    index = _components.Add( );
    _components.name[index] = "Big box";
    _components.size[index] = { 150, _screenSize.y - 100 };
    _components.position[index] = { 100, 50 };
    _components.velocityLimit[index] = { 0.0, 0.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.life[index] = 0;
    _components.attributes[index] = Attributes::Renderable | Attributes::Collision | Attributes::Collide;
    _components.states[index] = 0;
    _components.texture[index] = LoadTexture( resourcesPath + "water.bmp", _renderer );

    index = _components.Add( );
    _components.name[index] = "Small box";
    _components.size[index] = { 100, 100 };
    _components.position[index] = { _screenSize.x / 2 - 100,  _screenSize.y - 200 };
    _components.velocityLimit[index] = { 0.0, 0.0 };
    _components.velocity[index] = { 0.0, 0.0 };
    _components.acceleration[index] = { 0.0, 0.0 };
    _components.life[index] = 0;
    _components.attributes[index] = Attributes::Renderable | Attributes::Collision | Attributes::Collide;
    _components.states[index] = 0;
    _components.texture[index] = LoadTexture( _resourcesPath + "water.bmp", _renderer );
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

void Game::Loop( )
{
    while( true )
    {
        UpdateTime( );
        ProcessInput( );
        UpdateEntities( );
        Draw( );
    }
}

void Game::CreateProjectiles( const Vector2<int>& origin, const Vector2<int>& mouse, const Gun& gun )
{
    static double previous = 0;

    if( _timeCurrent - previous > gun.firingDelay )
    {
        previous = _timeCurrent;
        
        for( int i = 0; i < gun.projectiles; i++ )
        {
            const double ratio = tan( gun.spread * M_PI / 180.0 );
            Vector2<double> normal = NormalizeVector( { static_cast<double>( mouse.x - origin.x ), static_cast<double>( mouse.y - origin.y ) } ) * 50.0;
            Vector2<double> direction;
            Vector2<int> position;
            std::size_t index;

            if( ( normal.x > 0 && normal.y > 0 ) ||
                ( normal.x < 0 && normal.y < 0 ) )
            {
                normal.x += RandomNumberGenerator( -ratio, ratio );
                normal.y -= RandomNumberGenerator( -ratio, ratio );
            }
            else
            {
                normal.x += RandomNumberGenerator( -ratio, ratio );
                normal.y += RandomNumberGenerator( -ratio, ratio );
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

            position.x = origin.x + static_cast<int>( normal.x );
            position.y = origin.y + static_cast<int>( normal.y );

            direction = NormalizeVector( { static_cast<double>( position.x - origin.x ), static_cast<double>( position.y - origin.y ) } );

            position.x = position.x + static_cast<int>( RandomNumberGenerator( -ratio, ratio ) * 2.0 );
            position.y = position.y + static_cast<int>( RandomNumberGenerator( -ratio, ratio ) * 2.0 );

            index = _components.Add( );
            _components.name[index] = "Projectile";
            _components.size[index] = { 4, 4 };
            _components.position[index] = position;
            _components.velocity[index] = direction * gun.projectileVelocity;
            _components.acceleration[index] = direction * gun.projectileAcceleration;
            _components.life[index] = 100;
            _components.attributes[index] = Attributes::Renderable | Attributes::Collision | Attributes::Decay;
            _components.states[index] = 0;
            _components.texture[index] = LoadTexture( _resourcesPath + "white.bmp", _renderer );
        }
    }
}
void Game::UpdateTime( )
{
    _timePrevious = _timeCurrent;
    _timeCurrent = static_cast<double>( SDL_GetTicks( ) ) / 1000.0;
    _timeStep = _timeCurrent - _timePrevious;
}
void Game::ProcessInput( )
{
    while( SDL_PollEvent( &_event ) )
    {
        switch( _event.type )
        {
            case SDL_KEYDOWN:
            {
                switch( _event.key.keysym.sym )
                {
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
        Vector2<int> start = _components.position[_indexPlayer] + _components.size[_indexPlayer] / 2;
        Vector2<int> mouse;

        SDL_GetMouseState( &mouse.x, &mouse.y );
        CreateProjectiles( start, mouse, _libraryGuns.at( _components.guns[_indexPlayer] ) );
    }

    const Uint8* keyState = SDL_GetKeyboardState( nullptr );
    const double playerAcceleration = 10000.0;
    const double jumpVelocity = 2000.0;

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
    std::vector<std::size_t> indexesDelete;

    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        _components.velocity[index] = _components.velocity[index] + _components.acceleration[index] * _timeStep;

        if( _components.attributes[index] & Attributes::Friction )
        {
            _components.velocity[index] = Friction( _components.velocity[index], { 35.0, 0.0 } );
        }

        if( _components.attributes[index] & Attributes::Gravity &&
            _components.states[index] & States::Falling )
        {
            _components.velocity[index] = Gravity( _components.velocity[index], { 0.0, 70.0 } );
        }

        if( _components.attributes[index] & Attributes::VelocityLimit )
        {
            _components.velocity[index].x = Limit( _components.velocity[index].x, _components.velocityLimit[index].x );
            _components.velocity[index].y = Limit( _components.velocity[index].y, _components.velocityLimit[index].y );
        }

        _components.position[index].x = _components.position[index].x + static_cast<int>( _components.velocity[index].x * _timeStep );
        _components.position[index].y = _components.position[index].y + static_cast<int>( _components.velocity[index].y * _timeStep );

        _components.states[index] |= States::Falling;

        if( _components.attributes[index] & Attributes::Collision )
        {
            for( std::size_t indexCollision = 0; indexCollision < _components.indexCount; indexCollision++ )
            {
                if( indexCollision != index &&
                    _components.attributes[indexCollision] & Attributes::Collide )
                {
                    if( Collision( _components.position[index], _components.size[index], _components.position[indexCollision], _components.size[indexCollision] ) )
                    {
                        Vector2<double> zero = { 0.0, 0.0 };

                        if( _components.velocity[index] != zero )
                        {
                            _components.velocity[index] = zero;
                            _components.position[index] = OffsetPosition( _components.position[index], _components.size[index], _components.position[indexCollision], _components.size[indexCollision] );
                            _components.states[index] &= ~States::Falling;
                        }
                    }

                    if( _components.attributes[index] & Attributes::Gravity &&
                        _components.states[index] & States::Falling )
                    {
                        const Vector2<int> positionUnderneath = { _components.position[index].x, _components.position[index].y + _components.size[index].y + 1 };
                        const Vector2<int> sizeUnderneath = { _components.size[index].x, 1 };

                        if( Collision( positionUnderneath, sizeUnderneath, _components.position[indexCollision], _components.size[indexCollision] ) )
                        {
                            _components.states[index] &= ~States::Falling;
                        }
                    }
                }
            }
        }

        if( _components.attributes[index] & Attributes::Decay )
        {
            _components.life[index]--;

            if( _components.life[index] < 0 )
            {
                indexesDelete.push_back( index );
            }
        }

        if( OutOfBounds( _components.position[index] + _screenSize / 2, _screenSize * 10 ) )
        {
            if( _components.attributes[index] & Attributes::Decay )
            {
                indexesDelete.push_back( index );
            }
            else
            {
                _components.velocity[index] = { 0.0, 0.0 };
                _components.position[index] = _screenSize / 2;
            }
        }
    }
    
    std::sort( indexesDelete.begin( ), indexesDelete.end( ), std::greater<int>( ) );

    for( auto indexDelete : indexesDelete )
    {
        _components.Delete( indexDelete );
    }
}
void Game::Draw( )
{
    SDL_RenderClear( _renderer );

    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        if( _components.attributes[index] & Attributes::Renderable )
        {
            SDL_Rect destinationRect;

            destinationRect.x = _components.position[index].x;
            destinationRect.y = _components.position[index].y;
            destinationRect.w = _components.size[index].x;
            destinationRect.h = _components.size[index].y;

            SDL_RenderCopy( _renderer, _components.texture[index], nullptr, &destinationRect );
        }
    }

    SDL_RenderPresent( _renderer );
}