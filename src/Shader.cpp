#include "Shader.h"

#include <glad/glad.h>

#include <string>
#include <iostream>

namespace 
{
    unsigned int create_shader(const std::string& source, int type);
    bool check_shader_compilation(unsigned int shader);
    unsigned int create_program(unsigned int vertex_shader, unsigned int fragment_shader);
    bool check_shader_linking(unsigned int program_id);
}

Shader::Shader(const std::string &filename_vertex, const std::string &filename_fragment)
{
    setShaders(filename_vertex, filename_fragment);
}

Shader::~Shader()
{
    if (program_id_ != 0)
        glDeleteProgram(program_id_);
}

void Shader::setShaders(const std::string &filename_vertex, const std::string &filename_fragment)
{
    is_valid_ = false;

	const std::string vertex_shader_source = FileManager::getFileText(filename_vertex.c_str());
	const std::string fragment_shader_source = FileManager::getFileText(filename_fragment.c_str());

	unsigned int vertex_shader = create_shader(vertex_shader_source.c_str(), GL_VERTEX_SHADER);
    if (vertex_shader == 0)
        return;

    unsigned int fragment_shader = create_shader(fragment_shader_source.c_str(), GL_FRAGMENT_SHADER);
    if (fragment_shader == 0)
        return;

	program_id_ = create_program(vertex_shader, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    if (program_id_ == 0)
        return;

    is_valid_ = true;
}

void Shader::bind() const
{
    assert(isValid());
    glUseProgram(program_id_);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

unsigned int Shader::getUniformLocation(const std::string &name)
{
    return 0; // TODO 
}

namespace 
{
    unsigned int create_shader(const std::string& source, int type)
    {
        unsigned int shader_id;
        shader_id = glCreateShader(type);
        const char* str = source.c_str();
        glShaderSource(shader_id, 1, &str, nullptr);
        glCompileShader(shader_id);

        if (!check_shader_compilation(shader_id))
        {
            glDeleteShader(shader_id);
            return 0;
        }

        return shader_id;
    }

    bool check_shader_compilation(unsigned int shader)
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

    unsigned int create_program(unsigned int vertex_shader, unsigned int fragment_shader)
    {
        assert(vertex_shader != 0);
        assert(fragment_shader != 0);

        unsigned int shader_program;
        shader_program = glCreateProgram();

        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);

        glLinkProgram(shader_program);

        if (!check_shader_linking(shader_program))
        {
            glDeleteProgram(shader_program);
            shader_program = 0;
        }

        return shader_program;
    }

    bool check_shader_linking(unsigned int program_id)
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
}