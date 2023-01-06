#pragma once

class GLFWwindow;

class Input final
{
	friend class Engine;

public:
	static bool isKeyDown(int key);

private:
	Input() = default;
	~Input() = default;

	static Input& get();
	void init();

private:
	GLFWwindow *glfw_window_{nullptr};
};
