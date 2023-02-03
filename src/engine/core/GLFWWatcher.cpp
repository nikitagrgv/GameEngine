#include "GLFWWatcher.h"

#include "GLFW/glfw3.h"
#include "InputEnums.h"
#include "engine/core/events/InputEvents.h"
#include "engine/core/events/WindowEvents.h"

GLFWWatcher& GLFWWatcher::get()
{
    static GLFWWatcher instance;
    return instance;
}

void GLFWWatcher::init(GLFWwindow* glfw_window)
{
    glfwSetFramebufferSizeCallback(glfw_window,
        [](GLFWwindow* window, int width, int height) {
        GLFWWatcher::get().glfw_framebuffer_size_callback(width, height);
    });

    glfwSetKeyCallback(glfw_window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            GLFWWatcher::get().glfw_key_callback(key, scancode, action, mods);
        });

    glfwSetMouseButtonCallback(glfw_window,
        [](GLFWwindow* window, int button, int action, int mods) {
            GLFWWatcher::get().glfw_mouse_button_callback(button, action, mods);
        });

    glfwSetCursorPosCallback(glfw_window,
        [](GLFWwindow* window, double pos_x, double pos_y) {
            GLFWWatcher::get().glfw_cursor_pos_callback(pos_x, pos_y);
        });
}

int GLFWWatcher::addCallback(const std::function<void(EventPtr)>& callback, int categories)
{
    EventCallback event_callback;
    event_callback.callback = callback;
    event_callback.categories = categories;
    return callbacks_.add(event_callback);
}

void GLFWWatcher::removeCallback(int callback)
{
    callbacks_.remove(callback);
}

void GLFWWatcher::glfw_framebuffer_size_callback(int width, int height)
{
    for (int i = 0; i < callbacks_.count(); i++)
    {
        if (!Event::isInCategory(EVENT_CATEGORY_WINDOW, callbacks_[i].categories))
            continue;

        callbacks_[i].callback(std::make_unique<FramebufferSizeChangedEvent>(width, height));
    }
}

void GLFWWatcher::glfw_key_callback(int glfw_key, int scancode, int action, int mods)
{
    const Key key = getKeyFromGLFW(glfw_key);

    for (int i = 0; i < callbacks_.count(); i++)
    {
        if (!Event::isInCategory(EVENT_CATEGORY_INPUT, callbacks_[i].categories))
            continue;

        callbacks_[i].callback(std::make_unique<KeyPressEvent>(key,
            action == GLFW_PRESS         ? KeyState::PRESSED
                : action == GLFW_RELEASE ? KeyState::RELEASED
                                         : KeyState::REPEATED));
    }
}

void GLFWWatcher::glfw_mouse_button_callback(int glfw_button, int action, int mods)
{
    const MouseButton button = getMouseButtonFromGLFW(glfw_button);

    for (int i = 0; i < callbacks_.count(); i++)
    {
        if (!Event::isInCategory(EVENT_CATEGORY_INPUT, callbacks_[i].categories))
            continue;

        callbacks_[i].callback(std::make_unique<MousePressEvent>(
            button,
            action == GLFW_PRESS ? KeyState::PRESSED : KeyState::RELEASED));
    }
}

void GLFWWatcher::glfw_cursor_pos_callback(double pos_x, double pos_y)
{
    for (int i = 0; i < callbacks_.count(); i++)
    {
        if (!Event::isInCategory(EVENT_CATEGORY_INPUT, callbacks_[i].categories))
            continue;

        callbacks_[i].callback(std::make_unique<MouseMovedEvent>(
            pos_x,
            pos_y));
    }
}

void GLFWWatcher::shutdown()
{
    callbacks_.clear();
}
