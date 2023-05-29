#include "stdafx.h"
#include "Game_Engine.h"

int main()
{
    srand(static_cast<unsigned>(time(0)));
    Game_Engine game;
    
    game.Run();

    return 0;   
}