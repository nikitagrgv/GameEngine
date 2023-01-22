#include "ExampleGameLogic.h"

#include "Engine.h"
#include "FileManager.h"
#include "Input.h"
#include "OpenGLUtils.h"
#include "MathUtils.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

#include <iostream>

void ExampleGameLogic::init()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    imgui_init();

    // CONTROLS CALLBACKS
    Input::addKeyPressedCallback(GLFW_KEY_ESCAPE, []() {
        Engine::shutdownLater();
    });

    Input::addKeyPressedCallback(GLFW_KEY_F1, [this]() {
        wireframe_mode_ = !wireframe_mode_;
        std::cout << "Wireframe mode: " << wireframe_mode_ << std::endl;

    });

    Input::addKeyPressedCallback(GLFW_KEY_R, [this]() {
        std::cout << "Recompile all shaders..." << std::endl;
        compile_shaders();
    });

    Input::addMouseButtonPressedCallback(GLFW_MOUSE_BUTTON_RIGHT, [this]() {
        Input::setCursorEnabled(false);
    });
    Input::addMouseButtonReleasedCallback(GLFW_MOUSE_BUTTON_RIGHT, [this]() {
        Input::setCursorEnabled(true);
    });


    // ------------------------- SHADERS ------------------
    compile_shaders();

    // ------------------------- BUFFERS ------------------
    array_buffer_ = std::make_unique<VertexArray>();
    array_buffer_->bind();
    GL_CHECK_ERROR();

    index_buffer_ = std::make_unique<IndexBuffer>(indices_, sizeof(indices_) / sizeof(indices_[0]));
    vertex_buffer_ = std::make_unique<VertexBuffer>(vertices_, sizeof(vertices_));
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(3); // color
    layout.push<float>(2); // texture coordinates
    array_buffer_->addBuffer(*vertex_buffer_, layout);

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

    // ------------------------- CAMERA ------------------

    const auto fov = glm::radians(60.f);
    const float aspect = (float)Engine::getWidth() / (float)Engine::getHeight();
    const float z_near = 0.1f;
    const float z_far = 10000.f;

    camera_ = std::make_unique<Camera>(fov, aspect, z_near, z_far);
    camera_->setPosition(VEC_FORWARD * -2.f);

    // ------------------------- RENDERER ------------------
    renderer_.setBlending();
}

void ExampleGameLogic::render()
{
    // first
    {
        const auto transform_ = camera_->getProjection() * camera_->getView() * model_mat_;

        shader_->setUniform<float>("uTime", (float)Engine::getTime());
        shader_->setUniform<int>("uTexture", 0);
        shader_->setUniform<int>("uTexture_2", 1);
        shader_->setUniform<const glm::mat4&>("uTransform", transform_);

        texture0_->bind(0);
        texture1_->bind(1);

        renderer_.draw(*array_buffer_, *index_buffer_, *shader_);
    }

    // second
    {
        const auto transform_ = camera_->getProjection() * camera_->getView() * model2_mat_;

        shader_->setUniform<float>("uTime", (float)Engine::getTime());
        shader_->setUniform<int>("uTexture", 0);
        shader_->setUniform<int>("uTexture_2", 1);
        shader_->setUniform<const glm::mat4&>("uTransform", transform_);

        texture0_->bind(0);
        texture1_->bind(1);

        renderer_.draw(*array_buffer_, *index_buffer_, *shader_);
    }

    GL_CHECK_ERROR();

    imgui_before_draw();
    imgui_draw();
    imgui_after_draw();
}

void ExampleGameLogic::imgui_draw()
{
    ImGui::Begin("Another Window");
    if (ImGui::Checkbox("Wireframe mode", &wireframe_mode_))
        glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode_ ? GL_LINE : GL_FILL);

    std::string fps_text = "FPS: ";
    fps_text += std::to_string(Engine::getFps());
    ImGui::Text(fps_text.c_str());
    ImGui::End();

}

void ExampleGameLogic::update()
{
    const float dt = (float)Engine::getDelta();

    // camera rotation
    if (Input::isMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
        std::cout << Input::getMouseDelta().x << "  " <<  Input::getMouseDelta().y << std::endl;

        constexpr float speed = glm::radians(0.1f);

        const auto mouse_delta = Input::getMouseDelta();

        camera_->setYaw(camera_->getYaw() + (float)-mouse_delta.x * speed);
        camera_->setPitch(camera_->getPitch() + (float)-mouse_delta.y * speed);
    }

    // camera movement
    {
        constexpr float speed = 1.f;

        glm::vec3 offset{};

        if (Input::isKeyDown(GLFW_KEY_D))
            offset += getRight(camera_->getTransform());
        if (Input::isKeyDown(GLFW_KEY_A))
            offset -= getRight(camera_->getTransform());

        if (Input::isKeyDown(GLFW_KEY_W))
            offset += getForward(camera_->getTransform());
        if (Input::isKeyDown(GLFW_KEY_S))
            offset -= getForward(camera_->getTransform());

        if (Input::isKeyDown(GLFW_KEY_SPACE))
            offset += getUp(camera_->getTransform());
        if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
            offset -= getUp(camera_->getTransform());

        offset *= speed * dt;

        camera_->setPosition(camera_->getPosition() + offset);
    }

    // model rotation
    {
        constexpr float speed = glm::radians(45.f);

        int rot_dir_y = 0;
        if (Input::isKeyDown(GLFW_KEY_1))
            rot_dir_y += 1;
        if (Input::isKeyDown(GLFW_KEY_2))
            rot_dir_y -= 1;

        int rot_dir_x = 0;
        if (Input::isKeyDown(GLFW_KEY_3))
            rot_dir_x += 1;
        if (Input::isKeyDown(GLFW_KEY_4))
            rot_dir_x -= 1;

        model_mat_ = glm::rotate(model_mat_, (float)rot_dir_y * speed * dt, {0, 1, 0});
        model_mat_ = glm::rotate(model_mat_, (float)rot_dir_x * speed * dt, {1, 0, 0});
    }
}

void ExampleGameLogic::shutdown()
{
    imgui_shutdown();
}

void ExampleGameLogic::imgui_init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Engine::getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void ExampleGameLogic::imgui_shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ExampleGameLogic::imgui_before_draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ExampleGameLogic::imgui_after_draw()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

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
