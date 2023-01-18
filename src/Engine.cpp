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

    get().glfw_window_ = glfwCreateWindow(width, height, name, nullptr, nullptr);
    glfwMakeContextCurrent(get().glfw_window_);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    get().update_viewport_size(width, height);
    glfwSetFramebufferSizeCallback(get().glfw_window_,
        [](GLFWwindow* window, int width, int height) {
            Engine::get().update_viewport_size(width, height);
        });

    glEnable(GL_DEPTH_TEST);

    Input::get().init();
}

void Engine::run()
{
    for (auto* game : get().game_logics_)
        game->init();

    get().time_ = glfwGetTime();
    while (!glfwWindowShouldClose(get().glfw_window_))
    {
        double current_time = glfwGetTime();
        get().delta_time_ = current_time - get().time_;
        get().time_ = current_time;

        get().update();
        get().render();
        get().swap();

        glfwPollEvents();
        Input::get().update();
    }

    get().shutdown();
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
    get().game_logics_.push_back(game_logic);
}

void Engine::removeGameLogic(GameLogic* game_logic)
{
    const auto iterator = std::find(get().game_logics_.begin(), get().game_logics_.end(),
        game_logic);

    if (iterator != get().game_logics_.end())
        get().game_logics_.erase(iterator);
}

double Engine::getTime()
{
    return get().time_;
}

double Engine::getDelta()
{
    return get().delta_time_;
}

double Engine::getWidth()
{
    return get().width_;
}

double Engine::getHeight()
{
    return get().height_;
}

void Engine::shutdownLater()
{
    glfwSetWindowShouldClose(get().glfw_window_, true);
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

