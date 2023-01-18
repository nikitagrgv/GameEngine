#pragma once

#include <functional>
#include <vector>

class GLFWwindow;

class Input final
{
    friend class Engine;

public:
    static bool isKeyDown(int key);

    static bool isMouseButtonDown(int button);

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

    static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    // TODO refactor this! it's very dirty now

    int generate_id_key() const;
    bool has_id_key(int id) const;

    int generate_id_mouse_button() const;
    bool has_id_mouse_button(int id) const;


private:
    GLFWwindow* glfw_window_{nullptr};

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
