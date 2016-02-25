#include "Game.h"
#include "Enums.h"
#include <string>
#include <iostream>

int main( int argc, char* args[] )
{
    const std::string resourcesPath = "C:\\Users\\Erik\\Documents\\Visual Studio 2015\\Projects\\Shooter-SDL2\\Shooter-SDL2\\Resources\\";
    Game game( "Shooter-SDL2", resourcesPath, { 1280, 720 } );

    game.Loop( );

    return 0;
}