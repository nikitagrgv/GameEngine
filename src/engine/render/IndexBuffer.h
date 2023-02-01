#pragma once

class IndexBuffer
{
public:
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    IndexBuffer(IndexBuffer&& other) noexcept ;
    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    IndexBuffer(const unsigned int* data, int count);
    ~IndexBuffer();

    bool isValid() const { return buffer_id_ != 0; }

    int getCount() const { return count_; }

    void bind() const;
    void unbind() const;

private:
    void swap(IndexBuffer& other);

private:
    unsigned int buffer_id_{0};
    int count_{0};
};
