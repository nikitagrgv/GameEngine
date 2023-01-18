#include "Input.h"

#include "Engine.h"

bool Input::isKeyDown(int key)
{
    return glfwGetKey(get().glfw_window_, key);
}

bool Input::isMouseButtonDown(int button)
{
    return glfwGetMouseButton(get().glfw_window_, button);
}


int Input::addKeyPressedCallback(int key, const std::function<void()>& callback)
{
    KeyCallback key_callback;
    key_callback.callback_id = get().generate_id_key();
    key_callback.key = key;
    key_callback.callback = callback;
    key_callback.action = GLFW_PRESS;

    get().key_callbacks_.push_back(key_callback);

    return key_callback.callback_id;
}

int Input::addKeyReleasedCallback(int key, const std::function<void()>& callback)
{
    KeyCallback key_callback;
    key_callback.callback_id = get().generate_id_key();
    key_callback.key = key;
    key_callback.callback = callback;
    key_callback.action = GLFW_RELEASE;

    get().key_callbacks_.push_back(key_callback);

    return key_callback.callback_id;
}

void Input::removeKeyCallback(int callback_id)
{
    for (int i = 0; i < get().key_callbacks_.size(); i++)
    {
        if (get().key_callbacks_[i].callback_id == callback_id)
        {
            get().key_callbacks_.erase(get().key_callbacks_.begin() + i);
            return;
        }
    }
}

int Input::addMouseButtonPressedCallback(int button, const std::function<void()>& callback)
{
    MouseButtonCallback mouse_button_callback;
    mouse_button_callback.callback_id = get().generate_id_key();
    mouse_button_callback.button = button;
    mouse_button_callback.callback = callback;
    mouse_button_callback.action = GLFW_PRESS;

    get().mouse_button_callbacks_.push_back(mouse_button_callback);

    return mouse_button_callback.callback_id;
}

int Input::addMouseButtonReleasedCallback(int button, const std::function<void()>& callback)
{
    MouseButtonCallback mouse_button_callback;
    mouse_button_callback.callback_id = get().generate_id_key();
    mouse_button_callback.button = button;
    mouse_button_callback.callback = callback;
    mouse_button_callback.action = GLFW_RELEASE;

    get().mouse_button_callbacks_.push_back(mouse_button_callback);

    return mouse_button_callback.callback_id;
}

void Input::removeMouseButtonCallback(int callback_id)
{
    for (int i = 0; i < get().key_callbacks_.size(); i++)
    {
        if (get().key_callbacks_[i].callback_id == callback_id)
        {
            get().key_callbacks_.erase(get().key_callbacks_.begin() + i);
            return;
        }
    }
}

void Input::init()
{
    glfw_window_ = Engine::get().glfw_window_;
    glfwSetKeyCallback(glfw_window_, &Input::glfw_key_callback);
    glfwSetMouseButtonCallback(glfw_window_, &Input::glfw_mouse_button_callback);
}

Input& Input::get()
{
    static Input instance;
    return instance;
}

int Input::generate_id_key() const
{
    int id = 1;
    while (has_id_key(id))
        id++;

    return id;
}

bool Input::has_id_key(int id) const
{
    for (const auto& callback : key_callbacks_)
    {
        if (callback.callback_id == id)
            return true;
    }

    return false;
}

int Input::generate_id_mouse_button() const
{
    int id = 1;
    while (has_id_mouse_button(id))
        id++;

    return id;
}

bool Input::has_id_mouse_button(int id) const
{
    for (const auto& callback : mouse_button_callbacks_)
    {
        if (callback.callback_id == id)
            return true;
    }

    return false;
}

void Input::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    for (auto& callback : get().key_callbacks_)
    {
        if (callback.key != key)
            continue;

        if (callback.action == action)
            callback.callback();
    }
}

void Input::glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    for (auto& callback : get().mouse_button_callbacks_)
    {
        if (callback.button != button)
            continue;

        if (callback.action == action)
            callback.callback();
    }
}
