#include "Mesh.h"

#include <utility>

Mesh::Mesh(VertexArrayPtr vertex_array, IndexBufferPtr index_buffer, VertexBufferPtr vertex_buffer)
    : vertex_array_(std::move(vertex_array))
    , index_buffer_(std::move(index_buffer))
    , vertex_buffer_(std::move(vertex_buffer))
{}

MeshPtr Mesh::create(VertexArrayPtr vertex_array, IndexBufferPtr index_buffer,
    VertexBufferPtr vertex_buffer)
{
    return MeshPtr(
        new Mesh(std::move(vertex_array), std::move(index_buffer), std::move(vertex_buffer)));
}
