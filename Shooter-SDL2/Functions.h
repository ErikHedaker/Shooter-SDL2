#pragma once

#include "Vector2.h"
#include <SDL.h>
#include <string>


int RandomNumberGenerator( int min, int max );
double RandomNumberGenerator( double min, double max );
double Limit( double value, double limit );
bool OutOfBounds( const Vector2<double>& position, const Vector2<double>& limit );
bool Collision( const Vector2<double>& positionMoving, const Vector2<double>& sizeMoving, const Vector2<double>& positionStatic, const Vector2<double>& sizeStatic );
Vector2<double> OffsetCollisionPosition( const Vector2<double>& positionMoving, const Vector2<double>& sizeMoving, const Vector2<double>& positionStatic, const Vector2<double>& sizeStatic );
Vector2<double> OffsetCollisionVelocity( const Vector2<double>& positionMoving, const Vector2<double>& sizeMoving, const Vector2<double>& velocityMoving, const Vector2<double>& positionStatic, const Vector2<double>& sizeStatic );
Vector2<double> Friction( const Vector2<double>& velocity, const Vector2<double>& friction );
Vector2<double> Gravity( const Vector2<double>& velocity, const Vector2<double>& gravity );
Vector2<double> NormalizeVector( const Vector2<double>& vector );
SDL_Texture* LoadTexture( const std::string& file, SDL_Renderer* renderer );