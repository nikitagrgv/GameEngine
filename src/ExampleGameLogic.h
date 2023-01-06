#pragma once

#include "GameLogic.h"

class ExampleGameLogic final : public GameLogic
{
public:
	void init() override;
	void update() override;
	void render() override;
	void shutdown() override;

private:
	void check_shader_compilation(unsigned int shader_id) const;
	void check_shader_linking(unsigned int program_id) const;
	unsigned int create_vertex_shader(const char *vertex_shader_source) const;
	unsigned int create_fragment_shader(const char *fragment_shader_source) const;
	unsigned int create_shader_program(unsigned int vertex_shader, unsigned int fragment_shader) const;

private:
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
