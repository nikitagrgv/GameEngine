#include "ExampleGameLogic.h"
#include "engine/core/Engine.h"

#include <iostream>

int main()
{
    auto& engine = Engine::get();

    engine.init("Engine", 800, 600);

    ExampleGameLogic game_logic;
    engine.addGameLogic(&game_logic);

    engine.run();

    return 0;
}
