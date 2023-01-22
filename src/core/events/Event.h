#pragma once

#include "core/InputEnums.h"

enum class EventType
{
    None = 0,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseScrolled,
    MouseMoved
};

#define DECLARE_EVENT_METHODS(type)                                                                \
    static EventType getStaticType()                                                               \
    {                                                                                              \
        return EventType::type;                                                                    \
    }                                                                                              \
    virtual EventType getEventType() const override                                                \
    {                                                                                              \
        return getStaticType();                                                                    \
    }

class Event
{
public:
    Event() = default;
    virtual ~Event() = default;

    virtual EventType getEventType() const = 0;
};
