#include "ExampleGameLogic.h"

#include "Engine.h"
#include "Input.h"
#include "FileManager.h"

#include <iostream>

void ExampleGameLogic::init()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	compile_shaders();

	// CONTROLS CALLBACKS
	Input::addKeyPressedCallback(GLFW_KEY_Q, [this](){
		wireframe_mode_ = !wireframe_mode_;
		std::cout << "Wireframe mode: " << wireframe_mode_ << std::endl;

		glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode_ ? GL_LINE : GL_FILL);
	});

	Input::addKeyPressedCallback(GLFW_KEY_R, [this](){
		std::cout << "Recompile all shaders..." << std::endl;
		compile_shaders();
	});

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
	int uniform_time_location = glGetUniformLocation(shader_program_, "time");

	glUseProgram(shader_program_);
	glUniform1f(uniform_time_location, (float)Engine::getTime());

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
	glDeleteBuffers(1, &ebo_);
}

void ExampleGameLogic::compile_shaders()
{
	shaders_manager_.deleteAll();

	std::string vertex_shader_source = FileManager::getFileText("../shaders/vertex_shader.vert");
	std::string fragment_shader_source = FileManager::getFileText("../shaders/fragment_shader.frag");

	unsigned int vertex_shader = shaders_manager_.createVertexShader(vertex_shader_source.c_str());
	unsigned int fragment_shader = shaders_manager_.createFragmentShader(fragment_shader_source.c_str());
	shader_program_ = shaders_manager_.createProgram(vertex_shader, fragment_shader, true);
}
