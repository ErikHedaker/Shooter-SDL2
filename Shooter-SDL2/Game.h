#pragma once

#include "Vector2.h"
#include "Enums.h"
#include <SDL.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <functional>

struct Projectile
{
    int amount;
    double velocity;
    double acceleration;
    double delay;
    double spread;
};

struct Trait
{
    Trait( );
    Trait( const Representation& type, int value );
    Trait( const Representation& type, double value );
    Trait( const Representation& type, Projectile value );

    Representation type;

    union
    {
        int INT;
        double DOUBLE;
        Projectile PROJECTILE;
    };
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
    std::vector<std::vector<Trait>> trait;
    std::vector<int> attributes;
    std::vector<int> states;

    std::size_t Add( );
    void Delete( std::size_t index );
};

class Game
{
    public:
        Game( const std::string& name, const Vector2<double>& screenSize );
        ~Game( );

        void Start( );

    private:
        const std::string _name;
        const Vector2<double> _screenSize;
        const std::map<int, Projectile> _libraryProjectiles;

        Components _components;
        std::size_t _indexPlayer;
        std::vector<std::size_t> _indexesDelete;

        double _timePrevious;
        double _timeCurrent;
        double _timeStep;
        double _timeScale;

        bool _mouseButtonLeft;
        bool _mouseButtonRight;
        
        SDL_Event _event;
        SDL_Window* _window;
        SDL_Renderer* _renderer;

        void CreateProjectile( const Vector2<double>& origin, const Vector2<double>& mouse, const Projectile& projectile );
        void UpdateTime( );
        void ProcessInput( );
        void UpdateEntities( );
        void Draw( );

        void UpdateVelocity( );
        void ApplyFriction( );
        void ApplyGravity( );
        void ApplyVelocityLimit( );
        void UpdatePosition( );
        void HandleCollision( );
        void HandleLifetime( );
        void HandleOutOfBounds( );
        void DeleteEntities( );
};