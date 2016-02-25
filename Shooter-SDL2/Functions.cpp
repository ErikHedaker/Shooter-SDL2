#include "Functions.h"
#include <SDL.h>
#include <string>
#include <iostream>
#include <array>

SDL_Texture* LoadTexture( std::string file, SDL_Renderer* renderer )
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
double ApplyDrag( double value, double drag )
{
    if( value != 0.0 )
    {
        value = value + ( value > 0 ? -drag : drag );
    }

    if( value <  drag / 2.0 &&
        value > -drag / 2.0 )
    {
        value = 0.0;
    }

    return value;
}
double Limit( double value, double limit )
{
    if( value > limit )
    {
        value = limit;
    }

    if( value < -limit )
    {
        value = -limit;
    }

    return value;
}
bool OutOfBounds( const Vector2<int>& position, const Vector2<int>& limit )
{
    return
        position.x >  limit.x ||
        position.y >  limit.y ||
        position.x < -limit.x ||
        position.y < -limit.y;
}
bool Collision( const Vector2<int>& positionMoving, const Vector2<int>& sizeMoving, const Vector2<int>& positionStatic, const Vector2<int>& sizeStatic )
{
    return
        positionMoving.y + sizeMoving.y > positionStatic.y &&
        positionMoving.y < positionStatic.y + sizeStatic.y &&
        positionMoving.x + sizeMoving.x > positionStatic.x &&
        positionMoving.x < positionStatic.x + sizeStatic.x;
}
Vector2<int> OffsetPosition( const Vector2<int>& positionMoving, const Vector2<int>& sizeMoving, const Vector2<int>& positionStatic, const Vector2<int>& sizeStatic )
{
    const Vector2<int> centerMoving = positionMoving + sizeMoving / 2;
    const Vector2<int> centerStatic = positionStatic + sizeStatic / 2;
    Vector2<int> result = positionMoving;

    if( centerMoving.y > positionStatic.y && centerMoving.y < positionStatic.y + sizeStatic.y )
    {
        if( centerMoving.x < centerStatic.x )
        {
            result.x = centerStatic.x - sizeStatic.x / 2 - sizeMoving.x;
        }
        else
        {
            result.x = centerStatic.x + sizeStatic.x / 2;
        }
    }
    else
    {
        if( centerMoving.y < centerStatic.y )
        {
            result.y = centerStatic.y - sizeStatic.y / 2 - sizeMoving.y;
        }
        else
        {
            result.y = centerStatic.y + sizeStatic.y / 2;
        }
    }

    return result;
}