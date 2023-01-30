#include "Input.h"

#include "Engine.h"

Input::Input()
{
    init_lookup_tables();
}

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
    for (int i = 0; i < key_callbacks_.getNumObject(); i++)
    {
        auto& callback = key_callbacks_.getObject(i);
        if (callback.key != getKeyFromGLFW(key))
            continue;

        if (callback.action == action)
            callback.callback();
    }
}

void Input::glfw_mouse_button_callback(int button, int action, int mods)
{
    for (int i = 0; i < mouse_button_callbacks_.getNumObject(); i++)
    {
        auto& callback = mouse_button_callbacks_.getObject(i);

        if (callback.button != getMouseButtonFromGLFW(button))
            continue;

        if (callback.action == action)
            callback.callback();
    }
}

void Input::init_lookup_tables()
{
    lookup_key_from_glfw_.clear();
    lookup_glfw_from_key_.clear();

#define ADD_KEY(key)                                                                               \
    lookup_glfw_from_key_[static_cast<int>(Key::key)] = GLFW_##key;                                \
    lookup_key_from_glfw_[GLFW_##key] = static_cast<int>(Key::key)

    ADD_KEY(KEY_SPACE);
    ADD_KEY(KEY_APOSTROPHE);
    ADD_KEY(KEY_COMMA);
    ADD_KEY(KEY_MINUS);
    ADD_KEY(KEY_PERIOD);
    ADD_KEY(KEY_SLASH);
    ADD_KEY(KEY_0);
    ADD_KEY(KEY_1);
    ADD_KEY(KEY_2);
    ADD_KEY(KEY_3);
    ADD_KEY(KEY_4);
    ADD_KEY(KEY_5);
    ADD_KEY(KEY_6);
    ADD_KEY(KEY_7);
    ADD_KEY(KEY_8);
    ADD_KEY(KEY_9);
    ADD_KEY(KEY_SEMICOLON);
    ADD_KEY(KEY_EQUAL);
    ADD_KEY(KEY_A);
    ADD_KEY(KEY_B);
    ADD_KEY(KEY_C);
    ADD_KEY(KEY_D);
    ADD_KEY(KEY_E);
    ADD_KEY(KEY_F);
    ADD_KEY(KEY_G);
    ADD_KEY(KEY_H);
    ADD_KEY(KEY_I);
    ADD_KEY(KEY_J);
    ADD_KEY(KEY_K);
    ADD_KEY(KEY_L);
    ADD_KEY(KEY_M);
    ADD_KEY(KEY_N);
    ADD_KEY(KEY_O);
    ADD_KEY(KEY_P);
    ADD_KEY(KEY_Q);
    ADD_KEY(KEY_R);
    ADD_KEY(KEY_S);
    ADD_KEY(KEY_T);
    ADD_KEY(KEY_U);
    ADD_KEY(KEY_V);
    ADD_KEY(KEY_W);
    ADD_KEY(KEY_X);
    ADD_KEY(KEY_Y);
    ADD_KEY(KEY_Z);
    ADD_KEY(KEY_LEFT_BRACKET);
    ADD_KEY(KEY_BACKSLASH);
    ADD_KEY(KEY_RIGHT_BRACKET);
    ADD_KEY(KEY_GRAVE_ACCENT);
    ADD_KEY(KEY_WORLD_1);
    ADD_KEY(KEY_WORLD_2);
    ADD_KEY(KEY_ESCAPE);
    ADD_KEY(KEY_ENTER);
    ADD_KEY(KEY_TAB);
    ADD_KEY(KEY_BACKSPACE);
    ADD_KEY(KEY_INSERT);
    ADD_KEY(KEY_DELETE);
    ADD_KEY(KEY_RIGHT);
    ADD_KEY(KEY_LEFT);
    ADD_KEY(KEY_DOWN);
    ADD_KEY(KEY_UP);
    ADD_KEY(KEY_PAGE_UP);
    ADD_KEY(KEY_PAGE_DOWN);
    ADD_KEY(KEY_HOME);
    ADD_KEY(KEY_END);
    ADD_KEY(KEY_CAPS_LOCK);
    ADD_KEY(KEY_SCROLL_LOCK);
    ADD_KEY(KEY_NUM_LOCK);
    ADD_KEY(KEY_PRINT_SCREEN);
    ADD_KEY(KEY_PAUSE);
    ADD_KEY(KEY_F1);
    ADD_KEY(KEY_F2);
    ADD_KEY(KEY_F3);
    ADD_KEY(KEY_F4);
    ADD_KEY(KEY_F5);
    ADD_KEY(KEY_F6);
    ADD_KEY(KEY_F7);
    ADD_KEY(KEY_F8);
    ADD_KEY(KEY_F9);
    ADD_KEY(KEY_F10);
    ADD_KEY(KEY_F11);
    ADD_KEY(KEY_F12);
    ADD_KEY(KEY_F13);
    ADD_KEY(KEY_F14);
    ADD_KEY(KEY_F15);
    ADD_KEY(KEY_F16);
    ADD_KEY(KEY_F17);
    ADD_KEY(KEY_F18);
    ADD_KEY(KEY_F19);
    ADD_KEY(KEY_F20);
    ADD_KEY(KEY_F21);
    ADD_KEY(KEY_F22);
    ADD_KEY(KEY_F23);
    ADD_KEY(KEY_F24);
    ADD_KEY(KEY_F25);
    ADD_KEY(KEY_KP_0);
    ADD_KEY(KEY_KP_1);
    ADD_KEY(KEY_KP_2);
    ADD_KEY(KEY_KP_3);
    ADD_KEY(KEY_KP_4);
    ADD_KEY(KEY_KP_5);
    ADD_KEY(KEY_KP_6);
    ADD_KEY(KEY_KP_7);
    ADD_KEY(KEY_KP_8);
    ADD_KEY(KEY_KP_9);
    ADD_KEY(KEY_KP_DECIMAL);
    ADD_KEY(KEY_KP_DIVIDE);
    ADD_KEY(KEY_KP_MULTIPLY);
    ADD_KEY(KEY_KP_SUBTRACT);
    ADD_KEY(KEY_KP_ADD);
    ADD_KEY(KEY_KP_ENTER);
    ADD_KEY(KEY_KP_EQUAL);
    ADD_KEY(KEY_LEFT_SHIFT);
    ADD_KEY(KEY_LEFT_CONTROL);
    ADD_KEY(KEY_LEFT_ALT);
    ADD_KEY(KEY_LEFT_SUPER);
    ADD_KEY(KEY_RIGHT_SHIFT);
    ADD_KEY(KEY_RIGHT_CONTROL);
    ADD_KEY(KEY_RIGHT_ALT);
    ADD_KEY(KEY_RIGHT_SUPER);
    ADD_KEY(KEY_MENU);
#undef ADD_KEY

    lookup_glfw_from_mouse_button_.clear();
    lookup_mouse_button_from_glfw_.clear();

#define ADD_BUTTON(button)                                                                            \
    lookup_glfw_from_mouse_button_[static_cast<int>(MouseButton::button)] = GLFW_##button;                       \
    lookup_mouse_button_from_glfw_[GLFW_##button] = static_cast<int>(MouseButton::button)

    ADD_BUTTON(MOUSE_BUTTON_LEFT);
    ADD_BUTTON(MOUSE_BUTTON_RIGHT);
    ADD_BUTTON(MOUSE_BUTTON_MIDDLE);
    ADD_BUTTON(MOUSE_BUTTON_1);
    ADD_BUTTON(MOUSE_BUTTON_2);
    ADD_BUTTON(MOUSE_BUTTON_3);
    ADD_BUTTON(MOUSE_BUTTON_4);
    ADD_BUTTON(MOUSE_BUTTON_5);
    ADD_BUTTON(MOUSE_BUTTON_6);
    ADD_BUTTON(MOUSE_BUTTON_7);
    ADD_BUTTON(MOUSE_BUTTON_8);
#undef ADD_BUTTON
}
