#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{

public:
    VertexArray();
    ~VertexArray();

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    VertexArray(VertexArray&& other) noexcept;
    VertexArray& operator=(VertexArray&& other) noexcept;

    bool isValid() const { return buffer_id_ != 0; }

    void bind() const;
    void unbind() const;

    void addBuffer(const VertexBuffer& vertex_buffer, const VertexBufferLayout& layout);

private:
    void swap(VertexArray& other);

private:
    unsigned int buffer_id_{0};
};
