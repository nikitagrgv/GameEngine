#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "engine/core/Object.h"
#include "engine/core/SharedPtr.h"

class VertexArray;
using VertexArrayPtr = SharedPtr<VertexArray>;

class VertexArray final : public Object
{
public:
    static VertexArrayPtr create();

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    bool isValid() const { return buffer_id_ != 0; }

    void bind() const;
    void unbind() const;

    void addBuffer(const VertexBufferPtr& vertex_buffer, const VertexBufferLayout& layout);

private:
    VertexArray();
    ~VertexArray() override;

private:
    std::vector<VertexBufferPtr> vertex_buffers_;

    unsigned int buffer_id_{0};
};
