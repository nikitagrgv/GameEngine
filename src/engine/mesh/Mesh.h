#pragma once

#include "engine/core/Object.h"
#include "engine/render/IndexBuffer.h"
#include "engine/render/VertexArray.h"
#include "engine/render/VertexBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Mesh;
using MeshPtr = SharedPtr<Mesh>;

class Mesh final : public Object
{
public:
    static MeshPtr create(
        const VertexArrayPtr& vertex_array,
        const IndexBufferPtr& index_buffer,
        const VertexBufferPtr& vertex_buffer);

    struct Vertex
    {
        glm::vec3 position;
        glm::vec2 texture_coords;
        glm::vec3 normal;
    };

    VertexBufferPtr getVertexBuffer() const { return vertex_buffer_; }
    VertexArrayPtr getVertexArray() const { return vertex_array_; }
    IndexBufferPtr getIndexBuffer() const { return index_buffer_; }

private:
    Mesh(
        const VertexArrayPtr& vertex_array,
        const IndexBufferPtr& index_buffer,
        const VertexBufferPtr& vertex_buffer);
    ~Mesh() override = default;

private:
    VertexArrayPtr vertex_array_;
    IndexBufferPtr index_buffer_;
    VertexBufferPtr vertex_buffer_;
};
