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

    void bind() const;
    void unbind() const;

    void addBuffer(const VertexBuffer& vertex_buffer, const VertexBufferLayout layout);

private:
    unsigned int buffer_id_{0};
};
