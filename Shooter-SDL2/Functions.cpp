#include "Functions.h"
#include <SDL.h>
#include <string>
#include <iostream>

SDL_Texture* LoadTexture( const std::string& file, SDL_Renderer* renderer )
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* imageLoaded = nullptr;

    try
    {
        imageLoaded = SDL_LoadBMP( file.c_str( ) );

        if( imageLoaded == nullptr )
        {
            throw std::exception( SDL_GetError( ) );
        }

        texture = SDL_CreateTextureFromSurface( renderer, imageLoaded );
        SDL_FreeSurface( imageLoaded );

        if( texture == nullptr )
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

    return texture;
}