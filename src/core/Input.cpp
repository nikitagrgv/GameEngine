#include "Input.h"

#include "Engine.h"

#include "events/InputEvents.h"

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
    key_callback.action = KeyState::PRESSED;
    return key_callbacks_.add(key_callback);
}

int Input::addKeyReleasedCallback(Key key, const std::function<void()>& callback)
{
    KeyCallback key_callback;
    key_callback.key = key;
    key_callback.callback = callback;
    key_callback.action = KeyState::RELEASED;
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
    mouse_button_callback.action = KeyState::PRESSED;
    return mouse_button_callbacks_.add(mouse_button_callback);
}

int Input::addMouseButtonReleasedCallback(MouseButton button, const std::function<void()>& callback)
{
    MouseButtonCallback mouse_button_callback;
    mouse_button_callback.button = button;
    mouse_button_callback.callback = callback;
    mouse_button_callback.action = KeyState::RELEASED;
    return mouse_button_callbacks_.add(mouse_button_callback);
}

void Input::removeMouseButtonCallback(int callback_id)
{
    mouse_button_callbacks_.remove(callback_id);
}

void Input::init()
{
    glfw_window_ = Engine::get().glfw_window_;
}

void Input::update()
{
    const glm::dvec2 new_pos = getMousePosition();
    mouse_delta_ = new_pos - mouse_position_;
    mouse_position_ = new_pos;
}

void Input::shutdown()
{
    key_callbacks_.clear();
    mouse_button_callbacks_.clear();
}

Input& Input::get()
{
    static Input instance;
    return instance;
}

void Input::on_key_pressed(Key key)
{
    for (int i = 0; i < key_callbacks_.getNumObject(); i++)
    {
        auto& callback = key_callbacks_.getObject(i);

        if (callback.key == key && callback.action == KeyState::PRESSED)
            callback.callback();
    }
}

void Input::on_key_released(Key key)
{
    for (int i = 0; i < key_callbacks_.getNumObject(); i++)
    {
        auto& callback = key_callbacks_.getObject(i);

        if (callback.key == key && callback.action == KeyState::RELEASED)
            callback.callback();
    }
}

void Input::on_mouse_pressed(MouseButton button)
{
    for (int i = 0; i < mouse_button_callbacks_.getNumObject(); i++)
    {
        auto& callback = mouse_button_callbacks_.getObject(i);

        if (callback.button == button && callback.action == KeyState::PRESSED)
            callback.callback();
    }
}

void Input::on_mouse_released(MouseButton button)
{
    for (int i = 0; i < mouse_button_callbacks_.getNumObject(); i++)
    {
        auto& callback = mouse_button_callbacks_.getObject(i);

        if (callback.button == button && callback.action == KeyState::RELEASED)
            callback.callback();
    }
}

void Input::onEvent(EventPtr event)
{
    if (auto* e = dynamic_cast<KeyPressedEvent*>(event.get()))
    {
        on_key_pressed(e->getKey());
        return;
    }

    if (auto* e = dynamic_cast<KeyReleasedEvent*>(event.get()))
    {
        on_key_released(e->getKey());
        return;
    }

    if (auto* e = dynamic_cast<MouseButtonPressedEvent*>(event.get()))
    {
        on_mouse_pressed(e->getMouseButton());
        return;
    }

    if (auto* e = dynamic_cast<MouseButtonReleasedEvent*>(event.get()))
    {
        on_mouse_released(e->getMouseButton());
        return;
    }
}
