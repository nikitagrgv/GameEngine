#include "VertexArray.h"

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

void VertexArray::addBuffer(const VertexBufferPtr& vertex_buffer, const VertexBufferLayout& layout)
{
    // to prevent vertex buffer from deleting, we save strong reference to it. now vertex array manages it
    vertex_buffers_.push_back(vertex_buffer);

    bind();
    vertex_buffer->bind();

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

VertexArrayPtr VertexArray::create()
{
    return VertexArrayPtr(new VertexArray());
}
