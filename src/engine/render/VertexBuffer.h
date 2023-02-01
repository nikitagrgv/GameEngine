#pragma once

class VertexBuffer
{
public:
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    VertexBuffer(const void* data, int size);
    ~VertexBuffer();

    bool isValid() const { return buffer_id_ != 0; }

    void bind() const;
    void unbind() const;

private:
    void swap(VertexBuffer& other);

private:
    unsigned int buffer_id_{0};
};
