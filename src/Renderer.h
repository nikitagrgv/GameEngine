#pragma once

// clang-format off
#include <glad/glad.h>
// clang-format on

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <iostream>

#define GL_CHECK_ERROR()                                                                           \
    while (GLenum error = glGetError())                                                            \
    {                                                                                              \
        std::cout << "OpenGL error: " << error << std::endl;                                       \
    }

class Renderer
{    
public:
    Renderer();
    ~Renderer();

    void draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) const;

};


