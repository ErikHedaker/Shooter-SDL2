#include "Game.h"
#include "Enums.h"
#include <string>
#include <iostream>

int main( int argc, char* args[] )
{
    Game game( "Shooter-SDL2", { 1280.0, 720.0 } );

    game.Start( );

    return 0;
}