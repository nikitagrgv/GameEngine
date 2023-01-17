#include "Renderer.h"


Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) const
{
    vertex_array.bind();
    index_buffer.bind();
    shader.bind();

    glDrawElements(GL_TRIANGLES, index_buffer.getCount(), GL_UNSIGNED_INT, nullptr);

    vertex_array.unbind();
    index_buffer.unbind();
    shader.unbind();
}
