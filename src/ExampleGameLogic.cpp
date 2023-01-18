#include "ExampleGameLogic.h"

#include "Engine.h"
#include "FileManager.h"
#include "Input.h"
#include "OpenGLUtils.h"

#include <iostream>

void ExampleGameLogic::init()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // CONTROLS CALLBACKS
    Input::addKeyPressedCallback(GLFW_KEY_Q, [this]() {
        wireframe_mode_ = !wireframe_mode_;
        std::cout << "Wireframe mode: " << wireframe_mode_ << std::endl;

        glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode_ ? GL_LINE : GL_FILL);
    });

    Input::addKeyPressedCallback(GLFW_KEY_R, [this]() {
        std::cout << "Recompile all shaders..." << std::endl;
        compile_shaders();
    });

    // ------------------------- SHADERS ------------------
    compile_shaders();

    // ------------------------- BUFFERS ------------------
    array_buffer_ = std::make_unique<VertexArray>();
    array_buffer_->bind();
    GL_CHECK_ERROR();

    index_buffer_ = std::make_unique<IndexBuffer>(indices_, 6);
    vertex_buffer_ = std::make_unique<VertexBuffer>(vertices_, sizeof(vertices_));
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(3); // color
    layout.push<float>(2); // texture coordinates
    array_buffer_->addBuffer(*vertex_buffer_.get(), layout);

    // ------------------------- TEXTURES ------------------

    texture0_ = std::make_unique<Texture>("../data/textures/container.jpg");
    texture1_ = std::make_unique<Texture>("../data/textures/awesomeface.png");

    // ------------------------- UNBINDING ------------------

    array_buffer_->unbind();
    vertex_buffer_->unbind();
    index_buffer_->unbind();
    shader_->unbind();
    texture0_->unbind();
    texture1_->unbind();
}

void ExampleGameLogic::render()
{
    shader_->setUniform<float>("uTime", (float)Engine::getTime());
    shader_->setUniform<int>("uTexture", 0);
    shader_->setUniform<int>("uTexture_2", 1);

    texture0_->bind(0);
    texture1_->bind(1);

    renderer_.draw(*array_buffer_.get(), *index_buffer_.get(), *shader_.get());

    GL_CHECK_ERROR();
}

void ExampleGameLogic::update()
{
    if (Input::isKeyDown(GLFW_KEY_ESCAPE))
        Engine::shutdownLater();
}

void ExampleGameLogic::shutdown() {}

void ExampleGameLogic::compile_shaders()
{
    constexpr auto vertex_shader_filename = "../shaders/vertex_shader.vert";
    constexpr auto fragment_shader_filename = "../shaders/fragment_shader.frag";

    if (shader_)
        shader_->setShaders(vertex_shader_filename, fragment_shader_filename);
    else
        shader_ = std::make_unique<Shader>(vertex_shader_filename, fragment_shader_filename);

    if (!shader_->isValid())
        std::cout << "SHADER INVALID!" << std::endl;
}
