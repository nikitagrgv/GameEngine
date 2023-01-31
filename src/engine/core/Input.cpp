#include "Input.h"

#include "Engine.h"
#include "engine/core/events/InputEvents.h"

bool Input::isKeyDown(Key key)
{
    const auto& state = key_states_[key];
    return state == KeyState::DOWN || state == KeyState::PRESSED || state == KeyState::REPEATED;
}

bool Input::isMouseButtonDown(MouseButton button)
{
    const auto& state = mouse_button_states_[button];
    return state == KeyState::DOWN || state == KeyState::PRESSED; // mouse button cannot be repeated
}

bool Input::isKeyPressed(Key key)
{
    return key_states_[key] == KeyState::PRESSED;
}

bool Input::isKeyReleased(Key key)
{
    return key_states_[key] == KeyState::RELEASED;
}

bool Input::isKeyRepeated(Key key)
{
    return key_states_[key] == KeyState::REPEATED;
}

bool Input::isMouseButtonPressed(MouseButton button)
{
    return mouse_button_states_[button] == KeyState::PRESSED;
}

bool Input::isMouseButtonReleased(MouseButton button)
{
    return mouse_button_states_[button] == KeyState::RELEASED;
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

    clear_states();
}

void Input::clear_states()
{
    for (int i = 0; i < (int)Key::KEYS_COUNT; i++)
    {
        key_states_[(Key)i] = KeyState::UP;
    }
    for (int i = 0; i < (int)MouseButton::MOUSE_BUTTONS_COUNT; i++)
    {
        mouse_button_states_[(MouseButton)i] = KeyState::UP;
    }
}

void Input::update()
{
    const glm::dvec2 new_pos = getMousePosition();
    mouse_delta_ = new_pos - mouse_position_;
    mouse_position_ = new_pos;

    update_states();
}

void Input::update_states()
{
    for (auto& state : key_states_)
    {
        if (state.second == KeyState::PRESSED || state.second == KeyState::REPEATED)
        {
            state.second = KeyState::DOWN;
        }
        else if (state.second == KeyState::RELEASED)
        {
            state.second = KeyState::UP;
        }
    }

    for (auto& state : mouse_button_states_)
    {
        if (state.second == KeyState::PRESSED)
        {
            state.second = KeyState::DOWN;
        }
        else if (state.second == KeyState::RELEASED)
        {
            state.second = KeyState::UP;
        }
    }
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

void Input::handle_event(const KeyPressEvent& event)
{
    const auto key = event.getKey();
    const auto state = event.getState();

    key_states_[key] = state;

    for (int i = 0; i < key_callbacks_.count(); i++)
    {
        auto& callback = key_callbacks_[i];

        if (callback.key == key && callback.action == state)
            callback.callback();
    }
}

void Input::handle_event(const MousePressEvent& event)
{
    const auto button = event.getButton();
    const auto state = event.getState();

    mouse_button_states_[button] = state;

    for (int i = 0; i < mouse_button_callbacks_.count(); i++)
    {
        auto& callback = mouse_button_callbacks_[i];

        if (callback.button == button && callback.action == state)
            callback.callback();
    }
}

void Input::onEvent(EventPtr event)
{
    switch (event->getEventType())
    {
    case EventType::KeyPress: handle_event(static_cast<KeyPressEvent&>(*event));
    case EventType::MousePress: handle_event(static_cast<MousePressEvent&>(*event));
    default: break;
    }
}
