#include "ShadersManager.h"

#include <glad/glad.h>

#include <cassert>
#include <iostream>


ShadersManager::~ShadersManager()
{
	deleteAll();
}

void ShadersManager::deleteAll()
{
	deleteAllShaders();
	deleteAllPrograms();
}

void ShadersManager::deleteShader(unsigned int id)
{
	assert(has_shader(id));

	glDeleteShader(id);

	for (int i = 0; i < vertex_shaders_.size(); i++)
	{
		if (vertex_shaders_[i] == id)
		{
			vertex_shaders_.erase(vertex_shaders_.begin() + i);
			return;
		}
	}

	for (int i = 0; i < fragment_shaders_.size(); i++)
	{
		if (fragment_shaders_[i] == id)
		{
			fragment_shaders_.erase(fragment_shaders_.begin() + i);
			return;
		}
	}
}

void ShadersManager::deleteProgram(unsigned int id)
{
	assert(has_program(id));

	for (int i = 0; i < programs_.size(); i++)
	{
		if (programs_[i] == id)
		{
			programs_.erase(programs_.begin() + i);
			return;
		}
	}
}

bool ShadersManager::has_shader(unsigned int shader_id) const
{
	for (const unsigned int id : vertex_shaders_)
	{
		if (shader_id == id)
			return true;
	}

	for (const unsigned int id : fragment_shaders_)
	{
		if (shader_id == id)
			return true;
	}

	return false;
}

bool ShadersManager::has_program(unsigned int program_id) const
{
	for (const unsigned int id : programs_)
	{
		if (program_id == id)
			return true;
	}

	return false;
}

unsigned int ShadersManager::createVertexShader(const char *source)
{
	unsigned int shader_id = create_shader(source, GL_VERTEX_SHADER);

	if (shader_id != 0)
		vertex_shaders_.push_back(shader_id);

	return shader_id;
}

unsigned int ShadersManager::createFragmentShader(const char *source)
{
	unsigned int shader_id = create_shader(source, GL_FRAGMENT_SHADER);

	if (shader_id != 0)
		fragment_shaders_.push_back(shader_id);

	return shader_id;
}


unsigned int ShadersManager::create_shader(const char *source, int type)
{
	unsigned int shader_id;
	shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &source, nullptr);
	glCompileShader(shader_id);

	if (!check_shader_compilation(shader_id))
	{
		glDeleteShader(shader_id);
		return 0;
	}

	return shader_id;
}

bool ShadersManager::check_shader_compilation(unsigned int shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char info_log[512];
		glGetShaderInfoLog(shader, 512, nullptr, info_log);
		std::cout << "SHADER COMPILATION ERROR:\n" << info_log << std::endl;
	}

	return success;
}

unsigned int ShadersManager::createProgram(
	unsigned int vertex_shader,
	unsigned int fragment_shader,
	bool delete_shaders)
{
	assert(vertex_shader == 0 || has_shader(vertex_shader));
	assert(fragment_shader == 0 || has_shader(fragment_shader));

	unsigned int shader_program;
	shader_program = glCreateProgram();

	if (vertex_shader != 0)
		glAttachShader(shader_program, vertex_shader);

	if (fragment_shader != 0)
		glAttachShader(shader_program, fragment_shader);

	glLinkProgram(shader_program);

	if (!check_shader_linking(shader_program))
	{
		glDeleteShader(shader_program);
		shader_program = 0;
	}
	else
	{
		programs_.push_back(shader_program);
	}

	if (delete_shaders)
	{
		if (vertex_shader != 0)
			deleteShader(vertex_shader);
		if (fragment_shader != 0)
			deleteShader(fragment_shader);
	}

	return shader_program;
}

bool ShadersManager::check_shader_linking(unsigned int program_id)
{
	int success;
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		char info_log[512];
		glGetProgramInfoLog(program_id, 512, nullptr, info_log);
		std::cout << "LINKING COMPILATION ERROR:\n" << info_log << std::endl;
	}

	return success;
}

void ShadersManager::deleteAllShaders()
{
	deleteAllVertexShaders();
	deleteAllFragmentShaders();
}

void ShadersManager::deleteAllFragmentShaders()
{
	for (const unsigned int id : fragment_shaders_)
		glDeleteShader(id);
	fragment_shaders_.clear();
}

void ShadersManager::deleteAllVertexShaders()
{
	for (const unsigned int id : vertex_shaders_)
		glDeleteShader(id);
	vertex_shaders_.clear();
}

void ShadersManager::deleteAllPrograms()
{
	for (const unsigned int id : programs_)
		glDeleteProgram(id);
	programs_.clear();
}
