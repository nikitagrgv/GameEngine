#include "VertexArray.h"

VertexArray::VertexArray(VertexArray&& other) noexcept
{
    swap(other);
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
    if (this != &other)
        swap(other);

    return *this;
}

void VertexArray::swap(VertexArray& other)
{
    std::swap(this->buffer_id_, other.buffer_id_);
}

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &buffer_id_);
}

VertexArray::~VertexArray()
{
    if (buffer_id_)
        glDeleteVertexArrays(1, &buffer_id_);
}

void VertexArray::bind() const
{
    assert(isValid());
    glBindVertexArray(buffer_id_);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer &vertex_buffer, const VertexBufferLayout& layout)
{
    bind();
    vertex_buffer.bind();

    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}
