#pragma once

#include <functional>
#include <vector>

class GLFWwindow;

class Input final
{
    friend class Engine;

public:
    static bool isKeyDown(int key);

    static int addKeyPressedCallback(int key, std::function<void()> callback);
    static int addKeyReleasedCallback(int key, std::function<void()> callback);
    static void removeCallback(int callback_id);

private:
    Input() = default;
    ~Input() = default;

    static Input& get();
    void init();

    static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    int generate_id() const;
    bool has_id(int id) const;

private:
    GLFWwindow* glfw_window_{nullptr};

    struct KeyCallback
    {
        int callback_id;
        int key;
        int action; // pressed or released
        std::function<void()> callback;
    };

    std::vector<KeyCallback> callbacks_;
};
