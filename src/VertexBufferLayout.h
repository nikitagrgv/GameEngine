#pragma once

#include <glad/glad.h>

#include <vector>
#include <cassert>

struct VertexBufferElement
{
	unsigned int type;
	int count;
	bool normalized;

    static int getSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_INT: return 4;
        case GL_UNSIGNED_BYTE: return 1;
        }
        assert(0 && "Invalid type");
    }
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();
	~VertexBufferLayout();

    const std::vector<VertexBufferElement>& getElements() const { return elements_; }
    int getStride() const { return stride_; }

	template<typename T>
	void push(int count)
	{
		static_assert(0 && "Invalid type");
	}

	template<>
	void push<float>(int count)
	{
        do_push(count, GL_FLOAT);

	}

	template<>
	void push<unsigned int>(int count)
	{
        do_push(count, GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(int count)
	{
        do_push(count, GL_UNSIGNED_BYTE);
	}

private:
    void do_push(int count, unsigned int type)
    {
		elements_.push_back({type, count, false});
        stride_ += count * VertexBufferElement::getSizeOfType(type);
    }

private:
	std::vector<VertexBufferElement> elements_;
    int stride_{0};
};
