#include "VertexBuffer.h"

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

VertexBuffer::VertexBuffer(const void* data, int size)
{
    glGenBuffers(1, &buffer_id_);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &buffer_id_);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
