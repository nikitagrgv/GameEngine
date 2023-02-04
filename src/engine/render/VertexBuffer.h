#pragma once

#include "engine/core/Object.h"
#include "engine/core/SharedPtr.h"

class VertexBuffer;
using VertexBufferPtr = SharedPtr<VertexBuffer>;

class VertexBuffer final : public Object
{
public:
    static VertexBufferPtr create(const void* data, int size);

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    bool isValid() const { return buffer_id_ != 0; }

    void bind() const;
    void unbind() const;

private:
    VertexBuffer(const void* data, int size);
    ~VertexBuffer() override;

private:
    unsigned int buffer_id_{0};
};
