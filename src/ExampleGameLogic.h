#pragma once

#include "GameLogic.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

class ExampleGameLogic final : public GameLogic
{
public:
    void init() override;
    void update() override;
    void render() override;
    void shutdown() override;

private:
    void compile_shaders();

private:
    Renderer renderer_;

    std::unique_ptr<IndexBuffer> index_buffer_;
    std::unique_ptr<VertexBuffer> vertex_buffer_;
    std::unique_ptr<VertexArray> array_buffer_;
    std::unique_ptr<Shader> shader_;

    std::unique_ptr<Texture> texture0_;
    std::unique_ptr<Texture> texture1_;

    bool wireframe_mode_ = false;

    std::unique_ptr<Camera> camera_;

    glm::mat4 model_mat_{1};

    glm::mat4 model2_mat_{glm::translate(glm::mat4(1), {0.6, 0.6, 0})};

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texture_coordinates;
    };

    const Vertex vertices_[4]{
        {  {0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // top right
        { {0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // bottom right
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // bottom left
        { {-0.5f, 0.5f, 0.0f}, {0.8f, 0.1f, 0.8f}, {0.0f, 1.0f}}  // top left
    };

    const unsigned int indices_[6] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
};
