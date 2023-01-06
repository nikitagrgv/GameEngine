#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	constexpr int window_width = 800;
	constexpr int window_height = 600;

	GLFWwindow *window = glfwCreateWindow(window_width, window_height, "Window", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glViewport(0, 0, window_width, window_height);

	glClearColor(0.5, 0.2, 0.3, 1);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height){
		glViewport(0, 0, width, height);
	});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		cout << "key: " << key << " scancode: " << scancode << " action: " << action << " modes: " << mods << endl;
	});

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}