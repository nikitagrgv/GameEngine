#pragma once

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include <set>
#include <vector>

class GameLogic;
class Input;

class Engine final
{
    friend class Input;

public:
    static Engine& get();

    void init(const char* name, int width, int height);
    void run();
    void shutdownLater();

    void addGameLogic(GameLogic* game_logic);
    void removeGameLogic(GameLogic* game_logic);

    double getTime();
    double getDelta();
    double getFps();

    double getWidth();
    double getHeight();

    void* getWindow();

private:
    Engine() = default;
    ~Engine() = default;

    void shutdown();
    void update_viewport_size(int width, int height);

    void render();
    void update();
    void swap();

private:
    GLFWwindow* glfw_window_{nullptr};

    std::vector<GameLogic*> game_logics_;

    double time_{0};
    double delta_time_{0};

    int width_{0};
    int height_{0};
};
