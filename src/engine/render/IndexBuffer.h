#pragma once

#include "engine/core/Object.h"
#include "engine/core/SharedPtr.h"

class IndexBuffer;
using IndexBufferPtr = SharedPtr<IndexBuffer>;

class IndexBuffer final : public Object
{
public:
    static IndexBufferPtr create(const unsigned int* data, int count);

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    bool isValid() const { return buffer_id_ != 0; }

    int getCount() const { return count_; }

    void bind() const;
    void unbind() const;

private:
    IndexBuffer(const unsigned int* data, int count);
    ~IndexBuffer() override;

private:
    unsigned int buffer_id_{0};
    int count_{0};
};
