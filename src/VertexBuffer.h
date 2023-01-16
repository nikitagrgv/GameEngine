#pragma once

class VertexBuffer
{
public:
    VertexBuffer(const void* data, int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

private:
    unsigned int buffer_id_{0};
};