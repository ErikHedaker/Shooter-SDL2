#pragma once

#include "Vector2i.h"
#include <SDL.h>
#include <string>

SDL_Texture* LoadTexture( const std::string& file, SDL_Renderer* renderer );