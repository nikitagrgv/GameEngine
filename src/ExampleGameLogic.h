#pragma once

#include "GameLogic.h"
#include "ShadersManager.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

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
    std::unique_ptr<IndexBuffer> index_buffer_;
    std::unique_ptr<VertexBuffer> vertex_buffer_;
    std::unique_ptr<VertexArray> array_buffer_;

	ShadersManager shaders_manager_;

	bool wireframe_mode_ = false;

	unsigned int texture_;
	unsigned int texture2_;

	const float vertices_[4 * (3 + 3 + 2)] = {
		/*pos*/ 0.5f, 0.5f, 0.0f, /*col*/ 1.0f, 0.0f, 0.0f, /*tex*/ 1.0f, 1.0f,   // top right
		/*pos*/ 0.5f, -0.5f, 0.0f, /*col*/ 0.0f, 1.0f, 0.0f, /*tex*/ 1.0f, 0.0f,  // bottom right
		/*pos*/ -0.5f, -0.5f, 0.0f, /*col*/ 0.0f, 0.0f, 1.0f, /*tex*/ 0.0f, 0.0f, // bottom left
		/*pos*/ -0.5f, 0.5f, 0.0f, /*col*/ 0.8f, 0.1f, 0.8f, /*tex*/ 0.0f, 1.0f   // top left
	};

	const unsigned int indices_[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int shader_program_ = 0;
};
