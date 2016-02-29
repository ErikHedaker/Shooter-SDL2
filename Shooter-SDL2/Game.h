#pragma once

#include "Vector2.h"
#include <SDL.h>
#include <string>
#include <vector>
#include <map>

struct Gun
{
    std::string name;
    int projectiles;
    double projectileVelocity;
    double projectileAcceleration;
    double firingDelay;
    double spread;
};

struct Components
{
    std::size_t indexCount = 0;
    std::vector<std::string> name;
    std::vector<SDL_Texture*> texture;
    std::vector<Vector2<double>> size;
    std::vector<Vector2<double>> position;
    std::vector<Vector2<double>> velocityLimit;
    std::vector<Vector2<double>> velocity;
    std::vector<Vector2<double>> acceleration;
    std::vector<int> attributes;
    std::vector<int> states;
    std::vector<int> guns;
    std::vector<double> life;

    std::size_t Add( );
    void Delete( std::size_t index );
};

class Game
{
    public:
        Game( const std::string& name, const std::string& resourcesPath, const Vector2<double>& screenSize );
        ~Game( );

        void Loop( );

    private:
        const std::string _name;
        const std::string _resourcesPath;
        const Vector2<double> _screenSize;

        std::map<int, Gun> _libraryGuns;
        Components _components;
        std::size_t _indexPlayer;

        double _timePrevious;
        double _timeCurrent;
        double _timeStep;
        double _timeScale;

        bool _mouseButtonLeft;
        bool _mouseButtonRight;
        
        SDL_Event _event;
        SDL_Window* _window;
        SDL_Renderer* _renderer;

        void CreateProjectiles( const Vector2<double>& origin, const Vector2<double>& mouse, const Gun& gun );
        void UpdateTime( );
        void ProcessInput( );
        void UpdateEntities( );
        void Draw( );
};