#include "Game.h"
#include "Enums.h"
#include "Functions.h"
#include <iostream>

std::size_t Components::Add( )
{
    indexCount++;
    textures.emplace_back( );
    sizes.emplace_back( );
    positions.emplace_back( );
    velocities.emplace_back( );
    accelerations.emplace_back( );
    attributes.emplace_back( );

    return indexCount - 1;
}
void Components::Delete( std::size_t index )
{
    const std::size_t indexLast = indexCount - 1;

    std::swap( textures[index], textures[indexLast] );
    std::swap( sizes[index], sizes[indexLast] );
    std::swap( positions[index], positions[indexLast] );
    std::swap( velocities[index], velocities[indexLast] );
    std::swap( accelerations[index], accelerations[indexLast] );
    std::swap( attributes[index], attributes[indexLast] );

    indexCount--;
    textures.pop_back( );
    sizes.pop_back( );
    positions.pop_back( );
    velocities.pop_back( );
    accelerations.pop_back( );
    attributes.pop_back( );
}

Game::Game( const std::string& name, const Vector2i& screenSize ) :
    _name( name ),
    _screenSize( screenSize )
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
}
Game::~Game( )
{
    for( std::size_t index = 0; index < _components.indexCount; index++ )
    {
        if( _components.attributes[index] & Attributes::Renderable )
        {
            SDL_DestroyTexture( _components.textures[index] );
        }
    }

    SDL_DestroyRenderer( _renderer );
    SDL_DestroyWindow( _window );
    SDL_Quit( );
}

void Game::EntityAdd( const std::string& image, const Vector2i& size, const Vector2i& position, int attributes )
{
    std::size_t index = _components.Add( );

    _components.sizes[index] = size;
    _components.positions[index] = position;
    _components.velocities[index] = { 0, 0 };
    _components.accelerations[index] = { 0, 0 };
    _components.attributes[index] = attributes;

    if( _components.attributes[index] & Attributes::Renderable )
    {
        _components.textures[index] = LoadTexture( image, _renderer );
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

            destinationRect.x = _components.positions[index].x;
            destinationRect.y = _components.positions[index].y;
            destinationRect.w = _components.sizes[index].x;
            destinationRect.h = _components.sizes[index].y;

            SDL_RenderCopy( _renderer, _components.textures[index], nullptr, &destinationRect );
        }
    }

    SDL_RenderPresent( _renderer );
}
void Game::Loop( )
{
    while( true )
    {
        Draw( );
    }
}