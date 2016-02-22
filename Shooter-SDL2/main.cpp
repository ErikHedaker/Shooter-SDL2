#include "Game.h"
#include "Enums.h"
#include <string>
#include <iostream>

int main( int argc, char* args[] )
{
    const std::string pathResources = "C:\\Users\\Erik\\Documents\\Visual Studio 2015\\Projects\\Dungeoncrawler\\Dungeoncrawler\\Resources\\";
    Game game( "Shooter-SDL2", { 640, 480 } );

    game.EntityAdd( pathResources + "white.bmp", { 100, 100 }, { 100, 100 }, Attributes::Renderable );
    game.EntityAdd( pathResources + "grass.bmp", { 100, 100 }, { 200, 200 }, Attributes::Renderable );
    game.EntityAdd( pathResources + "white.bmp", { 100, 100 }, { 300, 100 }, Attributes::Renderable );

    game.Loop( );

    return 0;
}