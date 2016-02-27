#include "Game.h"
#include "Enums.h"
#include <string>
#include <iostream>

int main( int argc, char* args[] )
{
    const std::string name = "Shooter-SDL2";
    const std::string resourcesPath = "C:\\Users\\Erik\\Documents\\Visual Studio 2015\\Projects\\Shooter-SDL2\\Shooter-SDL2\\Resources\\";
    const Vector2<int> screenSize = { 1280, 720 };
    Game game( name, resourcesPath, screenSize );

    game.Loop( );

    return 0;
}