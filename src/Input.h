#pragma once

#include <functional>
#include <vector>

#include <glm/vec2.hpp>

class GLFWwindow;

// TODO refactor this! it's very dirty now. use some event system instead

class Input final
{
    friend class Engine;

public:
    static bool isKeyDown(int key);
    static bool isMouseButtonDown(int button);

    static glm::dvec2 getMousePosition();
    static glm::dvec2 getMouseDelta();

    static void setCursorEnabled(bool enabled);

    static int addKeyPressedCallback(int key, const std::function<void()>& callback);
    static int addKeyReleasedCallback(int key, const std::function<void()>& callback);
    static void removeKeyCallback(int callback_id);

    static int addMouseButtonPressedCallback(int button, const std::function<void()>& callback);
    static int addMouseButtonReleasedCallback(int button, const std::function<void()>& callback);
    static void removeMouseButtonCallback(int callback_id);

private:
    Input() = default;
    ~Input() = default;

    static Input& get();
    void init();
    void update();

    static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    int generate_id_key() const;
    bool has_id_key(int id) const;

    int generate_id_mouse_button() const;
    bool has_id_mouse_button(int id) const;

private:
    GLFWwindow* glfw_window_{nullptr};

    glm::dvec2 mouse_position_{};
    glm::dvec2 mouse_delta_{};

    struct KeyCallback
    {
        int callback_id;
        int key;
        int action; // pressed or released
        std::function<void()> callback;
    };
    std::vector<KeyCallback> key_callbacks_;

    struct MouseButtonCallback
    {
        int callback_id;
        int button;
        int action; // pressed or released
        std::function<void()> callback;
    };
    std::vector<MouseButtonCallback> mouse_button_callbacks_;
};
