#pragma once

#include "Vector2.h"
#include <SDL.h>
#include <string>

SDL_Texture* LoadTexture( std::string file, SDL_Renderer* renderer );
double ApplyDrag( double value, double drag );
double Limit( double value, double limit );
bool OutOfBounds( const Vector2<int>& position, const Vector2<int>& limit );
bool Collision( const Vector2<int>& positionMoving, const Vector2<int>& sizeMoving, const Vector2<int>& positionStatic, const Vector2<int>& sizeStatic );
Vector2<int> OffsetPosition( const Vector2<int>& positionMoving, const Vector2<int>& sizeMoving, const Vector2<int>& positionStatic, const Vector2<int>& sizeStatic );