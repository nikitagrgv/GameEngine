#include "Engine.h"
#include "ExampleGameLogic.h"

#include <iostream>

int main()
{
	Engine::init("Engine", 800, 600);

	ExampleGameLogic game_logic;
	Engine::addGameLogic(&game_logic);

	Engine::run();



//	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
//		cout << "key: " << key << " scancode: " << scancode << " action: " << action << " modes: " << mods << endl;
//	});
//


	return 0;
}

