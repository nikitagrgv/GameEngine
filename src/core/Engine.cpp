#include "Engine.h"

#include "GameLogic.h"
#include "Input.h"

#include <algorithm>

void Engine::init(const char* name, int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfw_window_ = glfwCreateWindow(width, height, name, nullptr, nullptr);
    glfwMakeContextCurrent(glfw_window_);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    update_viewport_size(width, height);
    glfwSetFramebufferSizeCallback(glfw_window_,
        [](GLFWwindow* window, int width, int height) {
            Engine::get().update_viewport_size(width, height);
        });

    glEnable(GL_DEPTH_TEST);

    Input::get().init();
}

void Engine::run()
{
    for (auto* game : game_logics_)
        game->init();

    time_ = glfwGetTime();
    while (!glfwWindowShouldClose(glfw_window_))
    {
        double current_time = glfwGetTime();
        delta_time_ = current_time - time_;
        time_ = current_time;

        update();
        render();
        swap();

        glfwPollEvents();
        Input::get().update();
    }

    shutdown();
}

void Engine::update_viewport_size(int width, int height)
{
    width_ = width;
    height_ = height;
    glViewport(0, 0, width, height);
}

Engine& Engine::get()
{
    static Engine instance;
    return instance;
}

void Engine::addGameLogic(GameLogic* game_logic)
{
    game_logics_.push_back(game_logic);
}

void Engine::removeGameLogic(GameLogic* game_logic)
{
    const auto iterator = std::find(game_logics_.begin(), game_logics_.end(),
        game_logic);

    if (iterator != game_logics_.end())
    {
        (*iterator)->shutdown();
        game_logics_.erase(iterator);
    }
}

double Engine::getTime()
{
    return time_;
}

double Engine::getDelta()
{
    return delta_time_;
}

double Engine::getFps()
{
    return 1. / getDelta();
}

double Engine::getWidth()
{
    return width_;
}

double Engine::getHeight()
{
    return height_;
}

void* Engine::getWindow()
{
    return glfw_window_;
}

void Engine::shutdownLater()
{
    glfwSetWindowShouldClose(glfw_window_, true);
}

void Engine::update()
{
    for (auto* game : game_logics_)
        game->update();
}

void Engine::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto* game : game_logics_)
        game->render();
}

void Engine::swap()
{
    glfwSwapBuffers(glfw_window_);
}

void Engine::shutdown()
{
    for (auto* game : game_logics_)
        game->shutdown();

    glfwTerminate();
}

