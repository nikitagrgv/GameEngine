#pragma once

#include "IdContainer.h"
#include "InputEnums.h"

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
    Key getKeyFromGLFW(int glfw_key)
    {
        return static_cast<Key>(lookup_key_from_glfw_[glfw_key]);
    }

    int getGLFWKey(Key key)
    {
        return lookup_glfw_from_key_[static_cast<int>(key)];
    }

    MouseButton getMouseButtonFromGLFW(int glfw_mouse_button)
    {
        return static_cast<MouseButton>(lookup_mouse_button_from_glfw_[glfw_mouse_button]);
    }

    int getGLFWMouseButton(MouseButton mouse_button)
    {
        return lookup_glfw_from_mouse_button_[static_cast<int>(mouse_button)];
    }

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
    Input();
    ~Input() = default;

    void init();
    void update();

    void init_lookup_tables();

    void glfw_key_callback(int key, int scancode, int action, int mods);
    void glfw_mouse_button_callback(int button, int action, int mods);

private:
    std::unordered_map<int, int> lookup_key_from_glfw_;
    std::unordered_map<int, int> lookup_glfw_from_key_;

    std::unordered_map<int, int> lookup_mouse_button_from_glfw_;
    std::unordered_map<int, int> lookup_glfw_from_mouse_button_;

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
