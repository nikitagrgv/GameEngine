#include "ExampleGameLogic.h"

#include "engine/core/Engine.h"
#include "engine/core/FileManager.h"
#include "engine/core/GLFWWatcher.h"
#include "engine/core/Input.h"
#include "engine/core/events/InputEvents.h"
#include "engine/core/events/WindowEvents.h"
#include "engine/mesh/ObjMeshLoader.h"
#include "engine/render/OpenGLUtils.h"
#include "engine/utils/MathUtils.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

#include <iostream>

void ExampleGameLogic::init()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    imgui_init();

    // ------------------------- SHADERS ------------------
    compile_shaders();

    // ------------------------- BUFFERS ------------------

    GL_CHECK_ERROR();

    ObjMeshLoader loader("../data/models/cube.obj");
    assert(loader.isLoaded());
    mesh_ = loader.getMesh();

    // ------------------------- TEXTURES ------------------

    texture0_ = Texture::create("../data/textures/container.jpg");
    texture1_ = Texture::create("../data/textures/awesomeface.png");

    // ------------------------- UNBINDING ------------------

    shader_->unbind();
    texture0_->unbind();
    texture1_->unbind();

    // ------------------------- CAMERA ------------------

    camera_ = std::make_unique<Camera>();
    camera_->setPosition(Math::VEC_FORWARD * -5.f);

    reload_camera_projection((float)engine.getWidth() / (float)engine.getHeight());
    glfw_watcher_callback_id_ = GLFWWatcher::get().addCallback(
        [this](const EventPtr& event) {
            if (const auto* e = event_cast<FramebufferSizeChangedEvent>(event.get()))
            {
                reload_camera_projection((float)e->getWidth() / (float)e->getHeight());
            }
        },
        EVENT_CATEGORY_WINDOW);

    // ------------------------- RENDERER ------------------
    renderer_.setBlending();

    // ------------------------- RENDERER ------------------
    Node::create("root", nullptr);
}

void ExampleGameLogic::reload_camera_projection(float aspect)
{
    constexpr auto fov = glm::radians(60.f);
    constexpr float z_near = 0.1f;
    constexpr float z_far = 10000.f;
    camera_->setPerspectiveProjection(fov, aspect, z_near, z_far);
}

void ExampleGameLogic::render()
{
    // first
    {
        const auto transform_ = camera_->getProjection() * camera_->getView() * model_mat_;

        shader_->setUniform<float>("uTime", (float)engine.getTime());
        shader_->setUniform<int>("uTexture", 0);
        shader_->setUniform<int>("uTexture_2", 1);
        shader_->setUniform<const glm::mat4&>("uTransform", transform_);

        texture0_->bind(0);
        texture1_->bind(1);

        renderer_.draw(*mesh_, *shader_);
    }

    // second
    {
        const auto transform_ = camera_->getProjection() * camera_->getView() * model2_mat_;

        shader_->setUniform<float>("uTime", (float)engine.getTime());
        shader_->setUniform<int>("uTexture", 0);
        shader_->setUniform<int>("uTexture_2", 1);
        shader_->setUniform<const glm::mat4&>("uTransform", transform_);

        texture0_->bind(0);
        texture1_->bind(1);

        renderer_.draw(*mesh_, *shader_);
    }

    GL_CHECK_ERROR();

    imgui_before_draw();
    imgui_draw();
    imgui_after_draw();
}

static int iii = 0;
std::string generate_name()
{
    iii++;
    return std::to_string(iii);
}

static void print_nodes(Node* node, int level = 0)
{
    auto& input = Input::get();

    std::string text;
    for (int i = 0; i < level; ++i)
        text += " ";

    text += node->getName();

    if (ImGui::Button(text.c_str()))
    {
        if (input.isKeyDown(Key::KEY_LEFT_SHIFT))
        {
            node->deleteForce();
            return;
        }
        else
        {
            Node::create(generate_name(), node);
        }
    }

    for (int i = 0; i < node->getNumChildren(); ++i)
    {
        print_nodes(node->getChild(i), level + 1);
    }
}

void ExampleGameLogic::imgui_draw()
{
    ImGui::Begin("Another Window");
    if (ImGui::Checkbox("Wireframe mode", &wireframe_mode_))
        glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode_ ? GL_LINE : GL_FILL);

    std::string fps_text = "FPS: ";
    fps_text += std::to_string(engine.getFps());
    ImGui::Text(fps_text.c_str());
    ImGui::End();

    ImGui::Begin("Hierarchy");
    ImGui::BeginChild("Scrolling");

    if (ImGui::Button("CREATE NEW ROOT NODE"))
        Node::create(generate_name());

    for (auto* node : Node::getAllNodes())
    {
        if (node->isRootNode())
            print_nodes(node);
    }
    ImGui::EndChild();
    ImGui::End();

}

void ExampleGameLogic::update()
{
    const float dt = (float)engine.getDelta();

    // input
    if (input.isKeyPressed(Key::KEY_ESCAPE))
        Engine::get().shutdownLater();

    if (input.isKeyPressed(Key::KEY_R))
    {
        std::cout << "Recompile all shaders..." << std::endl;
        compile_shaders();
    }

    if (input.isMouseButtonPressed(MouseButton::MOUSE_BUTTON_RIGHT))
        input.setCursorEnabled(false);

    if (input.isMouseButtonReleased(MouseButton::MOUSE_BUTTON_RIGHT))
        input.setCursorEnabled(true);
  
    // camera rotation
    if (input.isMouseButtonDown(MouseButton::MOUSE_BUTTON_RIGHT))
    {
        constexpr float speed = glm::radians(0.1f);

        const auto mouse_delta = input.getMouseDelta();

        camera_->setYaw(camera_->getYaw() + (float)-mouse_delta.x * speed);
        camera_->setPitch(camera_->getPitch() + (float)-mouse_delta.y * speed);
    }

    // camera movement
    {
        float speed = 1.f;

        if (input.isKeyDown(Key::KEY_LEFT_SHIFT))
            speed *= 4;

        glm::vec3 offset{};

        if (input.isKeyDown(Key::KEY_D))
            offset += Math::getRight(camera_->getTransform());
        if (input.isKeyDown(Key::KEY_A))
            offset -= Math::getRight(camera_->getTransform());

        if (input.isKeyDown(Key::KEY_W))
            offset += Math::getForward(camera_->getTransform());
        if (input.isKeyDown(Key::KEY_S))
            offset -= Math::getForward(camera_->getTransform());

        if (input.isKeyDown(Key::KEY_SPACE))
            offset += Math::getUp(camera_->getTransform());
        if (input.isKeyDown(Key::KEY_LEFT_CONTROL))
            offset -= Math::getUp(camera_->getTransform());

        offset *= speed * dt;

        camera_->setPosition(camera_->getPosition() + offset);
    }

    // model rotation
    {
        constexpr float speed = glm::radians(45.f);

        int rot_dir_y = 0;
        if (input.isKeyDown(Key::KEY_1))
            rot_dir_y += 1;
        if (input.isKeyDown(Key::KEY_2))
            rot_dir_y -= 1;

        int rot_dir_x = 0;
        if (input.isKeyDown(Key::KEY_3))
            rot_dir_x += 1;
        if (input.isKeyDown(Key::KEY_4))
            rot_dir_x -= 1;

        model_mat_ = glm::rotate(model_mat_, (float)rot_dir_y * speed * dt, {0, 1, 0});
        model_mat_ = glm::rotate(model_mat_, (float)rot_dir_x * speed * dt, {1, 0, 0});
    }
}

void ExampleGameLogic::shutdown()
{
    if (glfw_watcher_callback_id_ != -1)
        GLFWWatcher::get().removeCallback(glfw_watcher_callback_id_);
    imgui_shutdown();
}

void ExampleGameLogic::imgui_init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)engine.getWindow(), true);
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
        shader_ = Shader::create(vertex_shader_filename, fragment_shader_filename);

    if (!shader_->isValid())
        std::cout << "SHADER INVALID!" << std::endl;
}
