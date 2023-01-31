#pragma once

#include "Event.h"

class KeyPressEvent final : public Event
{
public:
    DECLARE_EVENT_METHODS(KeyPress, EVENT_CATEGORY_INPUT);

    explicit KeyPressEvent(Key key, KeyState state)
        : key_(key), state_(state)
    {}

    Key getKey() const { return key_; }
    KeyState getState() const { return state_; }

protected:
    Key key_;
    KeyState state_;
};

class MousePressEvent final : public Event
{
public:
    DECLARE_EVENT_METHODS(MousePress, EVENT_CATEGORY_INPUT);

    explicit MousePressEvent(MouseButton button, KeyState state)
        : button_(button), state_(state)
    {}

    MouseButton getButton() const { return button_; }
    KeyState getState() const { return state_; }

protected:
    MouseButton button_;
    KeyState state_;
};