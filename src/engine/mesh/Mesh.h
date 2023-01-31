#pragma once

#include "engine/render/IndexBuffer.h"
#include "engine/render/VertexArray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Mesh
{
public:
    struct Vertex
    {
        glm::vec3 position;
        glm::vec2 texture_coords;
        glm::vec3 normal;
    };

    const VertexArray& getVertexArray() const { return vertex_array_; }
    const IndexBuffer& getIndexBuffer() const { return index_buffer_; }
    VertexArray& getVertexArray() { return vertex_array_; }
    IndexBuffer& getIndexBuffer() { return index_buffer_; }

private:
    VertexArray vertex_array_;
    IndexBuffer index_buffer_;
};
