#pragma once

// clang-format off
#include <glad/glad.h>
// clang-format on

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <iostream>

class Renderer
{    
public:
    Renderer();
    ~Renderer();

    void draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) const;

};


