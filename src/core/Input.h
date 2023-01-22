#pragma once

#include "IdContainer.h"
#include "InputEnums.h"

#include "glm/vec2.hpp"
#include <functional>
#include <vector>

struct GLFWwindow;

// TODO refactor this! it's very dirty now. use some event system instead

class Input final
{
    friend class Engine;

public:
    bool isKeyDown(Key key);
    bool isMouseButtonDown(MouseButton button);

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

private:
    Input() = default;
    ~Input() = default;

    void init();
    void update();

    void glfw_key_callback(int key, int scancode, int action, int mods);
    void glfw_mouse_button_callback(int button, int action, int mods);

private:
    GLFWwindow* glfw_window_{nullptr};

    glm::dvec2 mouse_position_{};
    glm::dvec2 mouse_delta_{};

    struct KeyCallback
    {
        Key key;
        int action; // pressed or released
        std::function<void()> callback;
    };
    IdContainer<KeyCallback> key_callbacks_;

    struct MouseButtonCallback
    {
        MouseButton button;
        int action; // pressed or released
        std::function<void()> callback;
    };
    IdContainer<MouseButtonCallback> mouse_button_callbacks_;
};
