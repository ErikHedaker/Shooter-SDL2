#pragma once

#include "Vector2.h"
#include <SDL.h>
#include <string>


double Clip( double value, double lower, double upper );
double RandomNumberGenerator( double min, double max );
int RandomNumberGenerator( int min, int max );
bool OutOfBounds( const Vector2<double>& position, const Vector2<double>& limit );
bool Collision( const Vector2<double>& positionMoving, const Vector2<double>& sizeMoving, const Vector2<double>& positionStatic, const Vector2<double>& sizeStatic );
Vector2<double> OffsetCollisionSimple( const Vector2<double>& positionMoving, const Vector2<double>& sizeMoving, const Vector2<double>& positionStatic, const Vector2<double>& sizeStatic );
Vector2<double> OffsetCollision( const Vector2<double>& positionMoving, const Vector2<double>& sizeMoving, const Vector2<double>& velocityMoving, const Vector2<double>& positionStatic, const Vector2<double>& sizeStatic );
Vector2<double> NormalizeVector( const Vector2<double>& vector );
SDL_Texture* LoadTexture( const std::string& file, SDL_Renderer* renderer );