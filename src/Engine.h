#pragma once

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
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

    static void init(const char* name, int width, int height);
    static void run();
    static void shutdownLater();

    static void addGameLogic(GameLogic* game_logic);
    static void removeGameLogic(GameLogic* game_logic);

    static double getTime();
    static double getDelta();
    static double getFps();

    static double getWidth();
    static double getHeight();

    static void* getWindow();

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
