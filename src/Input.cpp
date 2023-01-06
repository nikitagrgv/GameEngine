#include "Input.h"

#include "Engine.h"

bool Input::isKeyDown(int key)
{
	return glfwGetKey(get().glfw_window_, key);
}

void Input::init()
{
	glfw_window_ = Engine::get().glfw_window_;
}

Input &Input::get()
{
	static Input instance;
	return instance;
}
