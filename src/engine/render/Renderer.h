#pragma once

// clang-format off
#include "glad/glad.h"
// clang-format on

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#include <iostream>

class Renderer
{    
public:
    Renderer();
    ~Renderer();

    void setBlending(); // TODO dummy method, later add some parameter

    void draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) const;

};


