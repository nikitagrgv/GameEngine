#pragma once

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* data, int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

private:
    unsigned int buffer_id_{0};
    int count_{0};
};
