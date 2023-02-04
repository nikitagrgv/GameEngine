#include "Renderer.h"


Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::draw(
    const VertexArrayPtr& vertex_array,
    const IndexBufferPtr& index_buffer,
    const ShaderPtr& shader) const
{
    shader->bind();
    vertex_array->bind();
    index_buffer->bind();

    glDrawElements(GL_TRIANGLES, index_buffer->getCount(), GL_UNSIGNED_INT, nullptr);

    vertex_array->unbind();
    index_buffer->unbind();
    shader->unbind();
}

void Renderer::draw(const MeshPtr& mesh, const ShaderPtr& shader) const
{
    draw(mesh->getVertexArray(), mesh->getIndexBuffer(), shader);
}

void Renderer::setBlending()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


