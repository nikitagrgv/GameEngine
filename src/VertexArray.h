#pragma once

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

class VertexArray
{

public:
    VertexArray();
    ~VertexArray();
    
    void bind() const;
    void unbind() const;

    void addBuffer(const VertexBuffer& vertex_buffer, const VertexBufferLayout layout);

private:
    unsigned int buffer_id_{0};
};

