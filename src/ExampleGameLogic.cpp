#include "ExampleGameLogic.h"

#include "Engine.h"
#include "Input.h"

#include <iostream>

void ExampleGameLogic::init()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// ----------------- SHADERS --------------------------

	const char *const vertex_shader_source = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;

		void main()
		{
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
		)";

	const char *const fragment_shader_source = R"(
		#version 330 core
		out vec4 FragColor;

		void main()
		{
		FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
		)";

	unsigned int vertex_shader = create_vertex_shader(vertex_shader_source);
	unsigned int fragment_shader = create_fragment_shader(fragment_shader_source);
	shader_program_ = create_shader_program(vertex_shader, fragment_shader);

	// delete shaders
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);


	// ------------------------- BUFFERS ------------------
	// create VAO and VBO
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);

	// use our VAO now
	glBindVertexArray(vao_);

	// use our VBO now
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	// copy vertices data to vbo buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);

	// use our EBO now
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	// copy indices to EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), &indices_, GL_STATIC_DRAW);

	// set vertex attribute 0 pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	// enable attribute 0
	glEnableVertexAttribArray(0);

	// unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// unbind VAO
	glBindVertexArray(0);
	// unbind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ExampleGameLogic::render()
{
	glUseProgram(shader_program_);
	glBindVertexArray(vao_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void ExampleGameLogic::update()
{
	if (Input::isKeyDown(GLFW_KEY_ESCAPE))
		Engine::shutdownLater();
}

void ExampleGameLogic::shutdown()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
	glDeleteProgram(shader_program_);
}

unsigned int ExampleGameLogic::create_shader_program(unsigned int vertex_shader,
	unsigned int fragment_shader) const
{
	unsigned int shader_program;
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	check_shader_linking(shader_program);

	return shader_program;
}

unsigned int ExampleGameLogic::create_vertex_shader(const char *const vertex_shader_source) const
{
	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
	glCompileShader(vertex_shader);

	check_shader_compilation(vertex_shader);

	return vertex_shader;
}

unsigned int ExampleGameLogic::create_fragment_shader(
	const char *const fragment_shader_source) const
{
	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
	glCompileShader(fragment_shader);

	check_shader_compilation(fragment_shader);

	return fragment_shader;
}

void ExampleGameLogic::check_shader_compilation(unsigned int shader_id) const
{
	int success;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char info_log[512];
		glGetShaderInfoLog(shader_id, 512, nullptr, info_log);
		std::cout << "SHADER COMPILATION ERROR:\n" << info_log << std::endl;
	}
}

void ExampleGameLogic::check_shader_linking(unsigned int program_id) const
{
	int success;
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		char info_log[512];
		glGetProgramInfoLog(program_id, 512, nullptr, info_log);
		std::cout << "LINKING COMPILATION ERROR:\n" << info_log << std::endl;
	}
}
