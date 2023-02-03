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
    void setKey(Key key) { key_ = key; }

    KeyState getState() const { return state_; }
    void setState(KeyState state) { state_ = state; }

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
    void setButton(MouseButton button) { button_ = button; }

    KeyState getState() const { return state_; }
    void setState(KeyState state) { state_ = state; }

protected:
    MouseButton button_;
    KeyState state_;
};

class MouseMovedEvent final : public Event
{
public:
    DECLARE_EVENT_METHODS(MouseMoved, EVENT_CATEGORY_INPUT);

    MouseMovedEvent(double pos_x, double pos_y)
        : pos_x_(pos_x)
        , pos_y_(pos_y)
    {}

    MouseMovedEvent(double pos_x, double pos_y, double delta_x, double delta_y)
        : pos_x_(pos_x)
        , pos_y_(pos_y)
        , delta_x_(delta_x)
        , delta_y_(delta_y)
        , delta_known_(true)
    {}

    double getPositionX() const { return pos_x_; }
    void setPositionX(double pos_x) { pos_x_ = pos_x; }

    double getPositionY() const { return pos_y_; }
    void setPositionY(double pos_y) { pos_y_ = pos_y; }

    double getDeltaX() const { return delta_x_; }
    void setDeltaX(double delta_x) { delta_x_ = delta_x; }

    double getDeltaY() const { return delta_y_; }
    void setDeltaY(double delta_y) { delta_y_ = delta_y; }

    bool isDeltaKnown() const { return delta_known_; }
    void setDeltaKnown(bool delta_known) { delta_known_ = delta_known; }

protected:
    double pos_x_{0};
    double pos_y_{0};
    double delta_x_{0};
    double delta_y_{0};
    bool delta_known_{false};
};
