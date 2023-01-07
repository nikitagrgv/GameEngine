#pragma once

#include "GameLogic.h"
#include "ShadersManager.h"

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
	ShadersManager shaders_manager_;

	bool wireframe_mode_ = false;

	const float vertices_[24] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
		-0.5f, 0.5f, 0.0f, 0.8f, 0.1f, 0.8f   // top left
	};

	const unsigned int indices_[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int ebo_ = 0;
	unsigned int vao_ = 0;
	unsigned int vbo_ = 0;
	unsigned int shader_program_ = 0;
};
