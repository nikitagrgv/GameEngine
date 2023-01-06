#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <set>
#include <vector>

class GameLogic;

class Engine final
{
public:
	static Engine &get();

	void init(const char *name, int width, int height);
	void run();
	void shutdownLater();

	void addGameLogic(GameLogic *game_logic);
	void removeGameLogic(GameLogic *game_logic);

	double getTime() const;
	double getDelta() const;

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
