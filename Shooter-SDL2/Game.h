#pragma once

#include "Vector2i.h"
#include <SDL.h>
#include <string>
#include <vector>

struct Components
{
    std::size_t indexCount = 0;
    std::vector<SDL_Texture*> textures;
    std::vector<Vector2i> sizes;
    std::vector<Vector2i> positions;
    std::vector<Vector2i> velocities;
    std::vector<Vector2i> accelerations;
    std::vector<int> attributes;

    std::size_t Add( );
    void Delete( std::size_t index );
};

class Game
{
    public:
        Game( const std::string& name, const Vector2i& screenSize );
        ~Game( );

        void EntityAdd( const std::string& image, const Vector2i& size, const Vector2i& position, int attributes );
        void Draw( );
        void Loop( );

    private:
        const std::string _name;
        Vector2i _screenSize;
        Components _components;
        SDL_Window* _window;
        SDL_Renderer* _renderer;
};