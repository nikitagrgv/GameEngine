#include "Input.h"

#include "Engine.h"

bool Input::isKeyDown(int key)
{
	return glfwGetKey(get().glfw_window_, key);
}

int Input::addKeyPressedCallback(int key, std::function<void()> callback)
{
	KeyCallback key_callback;
	key_callback.callback_id = get().generate_id();
	key_callback.key = key;
	key_callback.callback = callback;
	key_callback.action = GLFW_PRESS;

	get().callbacks_.push_back(key_callback);

	return key_callback.callback_id;
}

int Input::addKeyReleasedCallback(int key, std::function<void()> callback)
{
	KeyCallback key_callback;
	key_callback.callback_id = get().generate_id();
	key_callback.key = key;
	key_callback.callback = callback;
	key_callback.action = GLFW_RELEASE;

	get().callbacks_.push_back(key_callback);

	return key_callback.callback_id;
}

void Input::removeCallback(int callback_id)
{
	for (int i = 0; i < get().callbacks_.size(); i++)
	{
		if (get().callbacks_[i].callback_id == callback_id)
		{
			get().callbacks_.erase(get().callbacks_.begin() + i);
			return;
		}
	}
}

void Input::init()
{
	glfw_window_ = Engine::get().glfw_window_;
	glfwSetKeyCallback(glfw_window_, &Input::glfw_key_callback);
}

Input &Input::get()
{
	static Input instance;
	return instance;
}

int Input::generate_id() const
{
	int id = 1;
	while (has_id(id))
		id++;

	return id;
}

bool Input::has_id(int id) const
{
	for (const auto& callback : callbacks_)
	{
		if (callback.callback_id == id)
			return true;
	}

	return false;
}

void Input::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (auto &callback : get().callbacks_)
	{
		if (callback.key != key)
			continue;

		if (callback.action == action)
			callback.callback();
	}
}
