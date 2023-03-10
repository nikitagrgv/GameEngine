#pragma once

#include "IdContainer.h"
#include "engine/core/events/Event.h"

#include <functional>
#include <memory>

struct GLFWwindow;

class GLFWWatcher final
{
    friend class Engine;

public:
    static GLFWWatcher& get();

    int addCallback(const std::function<void(EventPtr)>& callback, int categories);
    void removeCallback(int callback);

private:
    GLFWWatcher() = default;
    ~GLFWWatcher() = default;

    void init(GLFWwindow* glfw_window);
    void shutdown();

    void glfw_framebuffer_size_callback(int width, int height);
    void glfw_key_callback(int glfw_key, int scancode, int action, int mods);
    void glfw_mouse_button_callback(int glfw_button, int action, int mods);
    void glfw_cursor_pos_callback(double pos_x, double pos_y);

private:
    struct EventCallback
    {
        std::function<void(EventPtr)> callback;
        int categories = EVENT_CATEGORY_NONE;
    };

    IdContainer<EventCallback> callbacks_;
};
