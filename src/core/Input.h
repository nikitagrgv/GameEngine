#pragma once

#include "IdContainer.h"
#include "InputEnums.h"
#include "events/Event.h"

#include "glm/vec2.hpp"
#include <functional>
#include <vector>
#include <unordered_map>

struct GLFWwindow;

// TODO refactor this! it's very dirty now. use some event system instead

class Input final
{
    friend class Engine;

public:
    bool isKeyDown(Key key);
    bool isMouseButtonDown(MouseButton button);

    bool isKeyPressed(Key key);
    bool isMouseButtonPressed(MouseButton button);

    bool isKeyReleased(Key key);
    bool isMouseButtonReleased(MouseButton button);

    glm::dvec2 getMousePosition();
    glm::dvec2 getMouseDelta();

    void setCursorEnabled(bool enabled);

    int addKeyPressedCallback(Key key, const std::function<void()>& callback);
    int addKeyReleasedCallback(Key key, const std::function<void()>& callback);
    void removeKeyCallback(int callback_id);

    int addMouseButtonPressedCallback(MouseButton button, const std::function<void()>& callback);
    int addMouseButtonReleasedCallback(MouseButton button, const std::function<void()>& callback);
    void removeMouseButtonCallback(int callback_id);

    static Input& get();

    void onEvent(EventPtr event);

private:
    Input() = default;
    ~Input() = default;

    void init();
    void update();
    void shutdown();

    void on_key_pressed(Key key);
    void on_key_released(Key key);
    void on_mouse_pressed(MouseButton button);
    void on_mouse_released(MouseButton button);

private:
    GLFWwindow* glfw_window_{nullptr};

    std::unordered_map<Key, KeyState> key_states_;
    std::unordered_map<MouseButton, KeyState> mouse_button_states_;

    glm::dvec2 mouse_position_{};
    glm::dvec2 mouse_delta_{};

    struct KeyCallback
    {
        Key key;
        KeyState action; // pressed or released
        std::function<void()> callback;
    };
    IdContainer<KeyCallback> key_callbacks_;

    struct MouseButtonCallback
    {
        MouseButton button;
        KeyState action; // pressed or released
        std::function<void()> callback;
    };
    IdContainer<MouseButtonCallback> mouse_button_callbacks_;
    void clear_states();
    void update_states();
};
