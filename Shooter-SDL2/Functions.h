#pragma once

#include "Vector2.h"
#include <SDL.h>
#include <string>

SDL_Texture* LoadTexture( const std::string& file, SDL_Renderer* renderer );
double Limit( double value, double limit );
bool OutOfBounds( const Vector2<int>& position, const Vector2<int>& limit );
bool Collision( const Vector2<int>& positionMoving, const Vector2<int>& sizeMoving, const Vector2<int>& positionStatic, const Vector2<int>& sizeStatic );
Vector2<int> OffsetPosition( const Vector2<int>& positionMoving, const Vector2<int>& sizeMoving, const Vector2<int>& positionStatic, const Vector2<int>& sizeStatic );
Vector2<double> Friction( const Vector2<double>& velocity, const Vector2<double>& friction );
Vector2<double> Gravity( const Vector2<double>& velocity, const Vector2<double>& gravity );
Vector2<double> NormalizeVector( const Vector2<double>& vector );