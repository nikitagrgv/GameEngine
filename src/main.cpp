#include "Engine.h"
#include "ExampleGameLogic.h"

#include <iostream>

int main()
{
    Engine::init("Engine", 800, 600);

    ExampleGameLogic game_logic;
    Engine::addGameLogic(&game_logic);

    Engine::run();

    return 0;
}
