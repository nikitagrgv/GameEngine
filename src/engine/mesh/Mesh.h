#pragma once

#include "engine/render/IndexBuffer.h"
#include "engine/render/VertexArray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texture_coords;
    glm::vec3 normal;
};

class Mesh
{
public:
    VertexArray& getVertexArray() const;
    IndexBuffer& getIndexBuffer() const;

private:
    VertexArray vertex_array_;
    IndexBuffer index_buffer_;

};
