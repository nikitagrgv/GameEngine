#pragma once

#include "Event.h"

class FramebufferSizeChangedEvent final : public Event
{
public:
    explicit FramebufferSizeChangedEvent(int width, int height)
        : width_(width)
        , height_(height)
    {}

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    DECLARE_EVENT_METHODS(FramebufferSizeChanged, EVENT_CATEGORY_WINDOW);

private:
    int width_{0};
    int height_{0};
};
