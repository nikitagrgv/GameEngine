#pragma once

#include "Event.h"

// ------------------------ KEY EVENTS ---------------------------------------

class KeyEvent : public Event
{
public:
    Key getKey() const { return key_; }

protected:
    explicit KeyEvent(Key key)
        : key_(key)
    {}

protected:
    Key key_;
};

class KeyPressedEvent final : public KeyEvent
{
public:
    explicit KeyPressedEvent(Key key)
        : KeyEvent(key)
    {}

    DECLARE_EVENT_METHODS(KeyPressed, EVENT_CATEGORY_INPUT);
};

class KeyReleasedEvent final : public KeyEvent
{
public:
    explicit KeyReleasedEvent(Key key)
        : KeyEvent(key)
    {}

    DECLARE_EVENT_METHODS(KeyReleased, EVENT_CATEGORY_INPUT);
};

// ------------------------ MOUSE BUTTON EVENTS  ---------------------------------------

class MouseButtonEvent : public Event
{
public:
    MouseButton getMouseButton() const { return mouse_button_; }

protected:
    explicit MouseButtonEvent(MouseButton mouse_button)
        : mouse_button_(mouse_button)
    {}

protected:
    MouseButton mouse_button_;
};

class MouseButtonPressedEvent final : public MouseButtonEvent
{
public:
    explicit MouseButtonPressedEvent(MouseButton mouse_button)
        : MouseButtonEvent(mouse_button)
    {}

    DECLARE_EVENT_METHODS(MouseButtonPressed, EVENT_CATEGORY_INPUT);
};

class MouseButtonReleasedEvent final : public MouseButtonEvent
{
public:
    explicit MouseButtonReleasedEvent(MouseButton mouse_button)
        : MouseButtonEvent(mouse_button)
    {}

    DECLARE_EVENT_METHODS(MouseButtonReleased, EVENT_CATEGORY_INPUT);
};
