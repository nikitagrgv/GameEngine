#include "ExampleGameLogic.h"

#include "Input.h"
#include "Engine.h"

void ExampleGameLogic::init()
{

}

void ExampleGameLogic::update()
{
	if (Input::isKeyDown(GLFW_KEY_ESCAPE))
		Engine::shutdownLater();
}

void ExampleGameLogic::render()
{

}
void ExampleGameLogic::shutdown()
{

}
