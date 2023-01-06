#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <set>
#include <vector>

class GameLogic;
class Input;

class Engine final
{
	friend class Input;

public:
	static Engine &get();

	static void init(const char *name, int width, int height);
	static void run();
	static void shutdownLater();

	static void addGameLogic(GameLogic *game_logic);
	static void removeGameLogic(GameLogic *game_logic);

	static double getTime();
	static double getDelta();

private:
	Engine() = default;
	~Engine() = default;

	void shutdown();
	void update_viewport_size(int width, int height) const;

private:
	GLFWwindow *glfw_window_{nullptr};

	std::vector<GameLogic*> game_logics_;

	double time_{0};
	double delta_time_{0};
	void render();
	void update();
	void swap();
};
