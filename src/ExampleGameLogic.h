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
	ShadersManager shaders_manager_;

	bool wireframe_mode_ = false;

	const float vertices_[12] = {
		0.5f, 0.5f, 0.0f,   // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f   // top left
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
