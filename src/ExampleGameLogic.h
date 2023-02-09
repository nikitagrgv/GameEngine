#pragma once

#include "engine/core/Camera.h"
#include "engine/core/Engine.h"
#include "engine/core/GameLogic.h"
#include "engine/core/Input.h"
#include "engine/render/IndexBuffer.h"
#include "engine/render/Renderer.h"
#include "engine/render/Shader.h"
#include "engine/render/Texture.h"
#include "engine/render/VertexArray.h"
#include "engine/render/VertexBuffer.h"
#include "engine/nodes/Node.h"

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
    void imgui_init();
    void imgui_shutdown();
    void imgui_before_draw();
    void imgui_draw();
    void imgui_after_draw();

    void compile_shaders();
    void reload_camera_projection(float aspect);

private:
    Input& input{Input::get()};
    Engine& engine{Engine::get()};

    Renderer renderer_;

    int glfw_watcher_callback_id_{-1};

    MeshPtr mesh_;
    ShaderPtr shader_;

    TexturePtr texture0_;
    TexturePtr texture1_;

    bool wireframe_mode_ = false;

    std::unique_ptr<Camera> camera_;

    glm::mat4 model_mat_{1};

    glm::mat4 model2_mat_{glm::translate(glm::mat4(1), {0.6, 0.6, 0})};
};
