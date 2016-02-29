#include "Functions.h"
#include <SDL.h>
#include <string>
#include <iostream>
#include <array>
#include <random>
#include <math.h>

int RandomNumberGenerator( int min, int max )
{
    static std::random_device rd;
    static std::mt19937 generator( rd( ) );
    std::uniform_int_distribution<int> randomNumber( min, max );

    return randomNumber( generator );
}
double RandomNumberGenerator( double min, double max )
{
    static std::random_device rd;
    static std::mt19937 generator( rd( ) );
    std::uniform_real_distribution<double> randomNumber( min, max );

    return randomNumber( generator );
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
Vector2<int> OffsetCollisionPosition( const Vector2<int>& positionMoving, const Vector2<int>& sizeMoving, const Vector2<int>& positionStatic, const Vector2<int>& sizeStatic )
{
    const Vector2<int> centerMoving = positionMoving + sizeMoving / 2;
    const Vector2<int> centerStatic = positionStatic + sizeStatic / 2;
    Vector2<int> result = positionMoving;

    if( !Collision( centerMoving, { 0, 0 }, positionStatic, sizeStatic ) &&
        centerMoving.y > positionStatic.y &&
        centerMoving.y < positionStatic.y + sizeStatic.y )
    {
        if( centerMoving.x < centerStatic.x )
        {
            result.x = positionStatic.x - sizeMoving.x;
        }
        else
        {
            result.x = positionStatic.x + sizeStatic.x;
        }
    }
    else
    {
        if( centerMoving.y < centerStatic.y )
        {
            result.y = positionStatic.y - sizeMoving.y;
        }
        else
        {
            result.y = positionStatic.y + sizeStatic.y;
        }
    }

    return result;
}
Vector2<int> OffsetCollisionVelocity( const Vector2<int>& positionMoving, const Vector2<int>& sizeMoving, const Vector2<double>& velocityMoving, const Vector2<int>& positionStatic, const Vector2<int>& sizeStatic )
{
    const Vector2<int> centerMoving = positionMoving + sizeMoving / 2;
    const Vector2<int> centerStatic = positionStatic + sizeStatic / 2;
    const Vector2<int> centerStaticLeft =  { positionStatic.x + sizeStatic.x / 4,                positionStatic.y + sizeStatic.y / 2 };
    const Vector2<int> centerStaticRight = { positionStatic.x - sizeStatic.x / 4 + sizeStatic.x, positionStatic.y + sizeStatic.y / 2 };
    Vector2<int> result = positionMoving;

    if( !Collision( centerMoving, { 0, 0 }, positionStatic, sizeStatic ) )
    {
        if( centerMoving.y > positionStatic.y &&
            centerMoving.y < positionStatic.y + sizeStatic.y )
        {
            if( centerMoving.x < centerStatic.x )
            {
                result.x = positionStatic.x - sizeMoving.x;
            }
            else
            {
                result.x = positionStatic.x + sizeStatic.x;
            }
        }
        else
        {
            if( centerMoving.y < centerStatic.y )
            {
                result.y = positionStatic.y - sizeMoving.y;
            }
            else
            {
                result.y = positionStatic.y + sizeStatic.y;
            }
        }
    }
    else
    {
        if( centerMoving.x < centerStaticLeft.x )
        {
            if( velocityMoving.x < 0 ||
                abs( velocityMoving.x ) < abs( velocityMoving.y ) )
            {
                if( velocityMoving.y > 0 )
                {
                    result.y = positionStatic.y - sizeMoving.y;
                }
                else
                {
                    result.y = positionStatic.y + sizeStatic.y;
                }
            }
            else
            {
                result.x = positionStatic.x - sizeMoving.x;
            }
        }
        else if( centerMoving.x > centerStaticRight.x )
        {
            if( velocityMoving.x > 0 ||
                abs( velocityMoving.x ) < abs( velocityMoving.y ) )
            {
                if( velocityMoving.y > 0 )
                {
                    result.y = positionStatic.y - sizeMoving.y;
                }
                else
                {
                    result.y = positionStatic.y + sizeStatic.y;
                }
            }
            else
            {
                result.x = positionStatic.x + sizeStatic.x;
            }
        }
        else
        {
            if( velocityMoving.y > 0 )
            {
                result.y = positionStatic.y - sizeMoving.y;
            }
            else
            {
                result.y = positionStatic.y + sizeStatic.y;
            }
        }
    }

    return result;
}
Vector2<double> Friction( const Vector2<double>& velocity, const Vector2<double>& friction )
{
    Vector2<double> result;

    if( velocity.x <  friction.x / 2.0 &&
        velocity.x > -friction.x / 2.0 )
    {
        result.x = 0.0;
    }
    else
    {
        result.x = velocity.x + ( velocity.x > 0 ? -friction.x : friction.x );
    }

    if( velocity.y <  friction.y / 2.0 &&
        velocity.y > -friction.y / 2.0 )
    {
        result.y = 0.0;
    }
    else
    {
        result.y = velocity.y + ( velocity.y > 0 ? -friction.y : friction.y );
    }

    return result;
}
Vector2<double> Gravity( const Vector2<double>& velocity, const Vector2<double>& gravity )
{
    return velocity + gravity;
}
Vector2<double> NormalizeVector( const Vector2<double>& vector )
{
    if( vector.x != 0.0 &&
        vector.y != 0.0 )
    {
        return vector / std::sqrt( vector.x * vector.x + vector.y * vector.y );
    }

    return { 0.0, 0.0 };
}
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