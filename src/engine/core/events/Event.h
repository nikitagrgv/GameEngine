#pragma once

#include "engine/core/InputEnums.h"

#include <memory>

enum class EventType
{
    None = 0,

    // INPUT
    KeyPress,
    MousePress,
    MouseScrolled,
    MouseMoved,

    // WINDOW
    FramebufferSizeChanged,
};

enum EventCategory
{
    EVENT_CATEGORY_NONE = 0,
    EVENT_CATEGORY_INPUT = 1 << 1,
    EVENT_CATEGORY_WINDOW = 1 << 2,

    EVENT_CATEGORY_ALL = EVENT_CATEGORY_INPUT | EVENT_CATEGORY_WINDOW,
};

#define DECLARE_EVENT_METHODS(type, categories)                                                    \
    static EventType getEventTypeStatic()                                                          \
    {                                                                                              \
        return EventType::type;                                                                    \
    }                                                                                              \
    virtual EventType getEventType() const override                                                \
    {                                                                                              \
        return getEventTypeStatic();                                                               \
    }                                                                                              \
    virtual int getEventCategories() const override                                                \
    {                                                                                              \
        return categories;                                                                         \
    }

class Event
{
public:
    Event() = default;
    virtual ~Event() = default;

    static bool isInCategory(EventCategory category, int categories)
    {
        return category & categories;
    }

    bool isInCategory(EventCategory category) const
    {
        return isInCategory(category, getEventCategories());
    }

    virtual EventType getEventType() const = 0;
    virtual int getEventCategories() const = 0;
};

using EventPtr = std::unique_ptr<Event>;

template <typename To, typename From>
To* event_cast(From* p)
{
    return p->getEventType() == To::getEventTypeStatic() ? static_cast<To*>(p) : nullptr;
}
