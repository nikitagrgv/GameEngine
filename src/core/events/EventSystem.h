#pragma once

#include "Event.h"

class EventSystem final
{
    friend class Engine;

public:
    static EventSystem& get();

private:
    EventSystem() = default;
    ~EventSystem() = default;

    void pushEvent(const Event& event);

private:


};
