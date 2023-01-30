#include "InputEnums.h"

#include "GLFW/glfw3.h"

#include <unordered_map>

namespace
{

struct LookupTables
{
    LookupTables();

    std::unordered_map<int, int> lookup_key_from_glfw_{};
    std::unordered_map<int, int> lookup_glfw_from_key_{};
    std::unordered_map<int, int> lookup_mouse_button_from_glfw_{};
    std::unordered_map<int, int> lookup_glfw_from_mouse_button_{};
} lookup_tables{};

} // namespace

Key getKeyFromGLFW(int glfw_key)
{
    return static_cast<Key>(lookup_tables.lookup_key_from_glfw_[glfw_key]);
}

int getGLFWKey(Key key)
{
    return lookup_tables.lookup_glfw_from_key_[static_cast<int>(key)];
}

MouseButton getMouseButtonFromGLFW(int glfw_mouse_button)
{
    return static_cast<MouseButton>(lookup_tables.lookup_mouse_button_from_glfw_[glfw_mouse_button]);
}

int getGLFWMouseButton(MouseButton mouse_button)
{
    return lookup_tables.lookup_glfw_from_mouse_button_[static_cast<int>(mouse_button)];
}

namespace
{

LookupTables::LookupTables()
{
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

#define ADD_BUTTON(button)                                                                         \
    lookup_glfw_from_mouse_button_[static_cast<int>(MouseButton::button)] = GLFW_##button;         \
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

}