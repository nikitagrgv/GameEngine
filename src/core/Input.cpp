#include "Input.h"

#include "Engine.h"

bool Input::isKeyDown(Key key)
{
    return glfwGetKey(glfw_window_, getGLFWKey(key));
}

bool Input::isMouseButtonDown(MouseButton button)
{
    return glfwGetMouseButton(glfw_window_, getGLFWMouseButton(button));
}

glm::dvec2 Input::getMousePosition()
{
    glm::dvec2 pos;
    glfwGetCursorPos(glfw_window_, &pos.x, &pos.y);
    return pos;
}

glm::dvec2 Input::getMouseDelta()
{
    return mouse_delta_;
}

void Input::setCursorEnabled(bool enabled)
{
    glfwSetInputMode(glfw_window_, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    update();
    mouse_delta_ = {0, 0};
}

int Input::addKeyPressedCallback(Key key, const std::function<void()>& callback)
{
    KeyCallback key_callback;
    key_callback.key = key;
    key_callback.callback = callback;
    key_callback.action = GLFW_PRESS;
    return key_callbacks_.add(key_callback);
}

int Input::addKeyReleasedCallback(Key key, const std::function<void()>& callback)
{
    KeyCallback key_callback;
    key_callback.key = key;
    key_callback.callback = callback;
    key_callback.action = GLFW_RELEASE;
    return key_callbacks_.add(key_callback);
}

void Input::removeKeyCallback(int callback_id)
{
    key_callbacks_.remove(callback_id);
}

int Input::addMouseButtonPressedCallback(MouseButton button, const std::function<void()>& callback)
{
    MouseButtonCallback mouse_button_callback;
    mouse_button_callback.button = button;
    mouse_button_callback.callback = callback;
    mouse_button_callback.action = GLFW_PRESS;
    return mouse_button_callbacks_.add(mouse_button_callback);
}

int Input::addMouseButtonReleasedCallback(MouseButton button, const std::function<void()>& callback)
{
    MouseButtonCallback mouse_button_callback;
    mouse_button_callback.button = button;
    mouse_button_callback.callback = callback;
    mouse_button_callback.action = GLFW_RELEASE;
    return mouse_button_callbacks_.add(mouse_button_callback);
}

void Input::removeMouseButtonCallback(int callback_id)
{
    mouse_button_callbacks_.remove(callback_id);
}

void Input::init()
{
    glfw_window_ = Engine::get().glfw_window_;
    glfwSetKeyCallback(glfw_window_, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Input::get().glfw_key_callback(key, scancode, action, mods);
    });
    
    glfwSetMouseButtonCallback(glfw_window_, [](GLFWwindow* window, int button, int action, int mods)
    {
        Input::get().glfw_mouse_button_callback(button, action, mods);
    });
}

void Input::update()
{
    const glm::dvec2 new_pos = getMousePosition();
    mouse_delta_ = new_pos - mouse_position_;
    mouse_position_ = new_pos;
}

Input& Input::get()
{
    static Input instance;
    return instance;
}

void Input::glfw_key_callback(int key, int scancode, int action, int mods)
{
    for (auto& callback : key_callbacks_)
    {
        if (callback.key != getKeyFromGLFW(key))
            continue;

        if (callback.action == action)
            callback.callback();
    }
}

void Input::glfw_mouse_button_callback(int button, int action, int mods)
{
    for (auto& callback : mouse_button_callbacks_)
    {
        if (callback.button != getMouseButtonFromGLFW(button))
            continue;

        if (callback.action == action)
            callback.callback();
    }
}
