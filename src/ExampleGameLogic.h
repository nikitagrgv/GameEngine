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
	unsigned int create_vertex_shader(const char *const vertex_shader_source) const;
	unsigned int create_fragment_shader(const char *const fragment_shader_source) const;
	unsigned int create_shader_program(unsigned int vertex_shader,
		unsigned int fragment_shader) const;
};
