#include "IndexBuffer.h"

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include <algorithm>
#include <cassert>

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
{
    swap(other);
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
    if (this != &other)
        swap(other);

    return *this;
}

void IndexBuffer::swap(IndexBuffer& other)
{
    std::swap(this->buffer_id_, other.buffer_id_);
    std::swap(this->count_, other.count_);
}

IndexBuffer::IndexBuffer(const unsigned int* data, int count)
    : count_(count)
{
    glGenBuffers(1, &buffer_id_);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    if (buffer_id_)
        glDeleteBuffers(1, &buffer_id_);
}

void IndexBuffer::bind() const
{
    assert(isValid());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
