#pragma once

#include "Vector2.h"
#include "Player.h"
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
        Game( std::string name, std::string resourcesPath, Vector2<int> screenSize );
        ~Game( );

        void Loop( );

    private:
        const std::string _name;
        const std::string _resourcesPath;
        Vector2<int> _screenSize;
        Components _components;
        std::size_t _indexPlayer;
        Player _player;

        double _timePrevious;
        double _timeCurrent;
        double _timeStep;
        
        SDL_Event _event;
        SDL_Window* _window;
        SDL_Renderer* _renderer;

        void EntityAdd( const std::string& name, const std::string& texturePath, const Vector2<int>& position, const Vector2<int>& size, const Vector2<double>& velocityMax, const Vector2<double>& velocity, const Vector2<double>& acceleration, int attributes, int states );
        void CreateProjectile( const Vector2<int>& origin, const Vector2<int>& mouse );
        void UpdateTime( );
        void ProcessInput( );
        void UpdateEntities( );
        void Draw( );
};