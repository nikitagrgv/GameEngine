#include "Engine.h"
#include "ExampleGameLogic.h"

#include <iostream>

int main()
{
	auto& game = Engine::get();
	game.init("Engine", 800, 600);

	ExampleGameLogic game_logic;
	game.addGameLogic(&game_logic);

	game.run();

//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);


//	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
//		cout << "key: " << key << " scancode: " << scancode << " action: " << action << " modes: " << mods << endl;
//	});
//


	return 0;
}

