#pragma once

// clang-format off
#include "glad/glad.h"
// clang-format on

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "engine/mesh/Mesh.h"

#include <iostream>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void setBlending(); // TODO dummy method, later add some parameter

    void draw(
        const VertexArrayPtr& vertex_array,
        const IndexBufferPtr& index_buffer,
        const ShaderPtr& shader) const;
    
    void draw(const MeshPtr& mesh, const ShaderPtr& shader) const;
};
