#include "Mesh.h"

Mesh::Mesh(
    const VertexArrayPtr& vertex_array,
    const IndexBufferPtr& index_buffer,
    const VertexBufferPtr& vertex_buffer)
    : vertex_array_(vertex_array)
    , index_buffer_(index_buffer)
    , vertex_buffer_(vertex_buffer)
{}

MeshPtr Mesh::create(
    const VertexArrayPtr& vertex_array,
    const IndexBufferPtr& index_buffer,
    const VertexBufferPtr& vertex_buffer)
{
    return MeshPtr(new Mesh(vertex_array, index_buffer, vertex_buffer));
}
