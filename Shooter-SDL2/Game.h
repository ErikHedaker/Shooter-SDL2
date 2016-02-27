#pragma once

#include "Vector2.h"
#include <SDL.h>
#include <string>
#include <vector>

struct Components
{
    std::size_t indexCount = 0;
    std::vector<std::string> name;
    std::vector<SDL_Texture*> texture;
    std::vector<Vector2<int>> size;
    std::vector<Vector2<int>> position;
    std::vector<Vector2<double>> velocityMax;
    std::vector<Vector2<double>> velocity;
    std::vector<Vector2<double>> acceleration;
    std::vector<int> life;
    std::vector<int> attributes;
    std::vector<int> states;

    std::size_t Add( );
    void Delete( std::size_t index );
};

class Game
{
    public:
        Game( const std::string& name, const std::string& resourcesPath, const Vector2<int>& screenSize );
        ~Game( );

        void Loop( );

    private:
        const std::string _name;
        const std::string _resourcesPath;
        const Vector2<int> _screenSize;

        Components _components;
        std::size_t _indexPlayer;

        double _timePrevious;
        double _timeCurrent;
        double _timeStep;

        bool _mouseButtonLeft;
        bool _mouseButtonRight;
        
        SDL_Event _event;
        SDL_Window* _window;
        SDL_Renderer* _renderer;

        void CreateProjectile( const Vector2<int>& origin, const Vector2<int>& mouse );
        void UpdateTime( );
        void ProcessInput( );
        void UpdateEntities( );
        void Draw( );
};