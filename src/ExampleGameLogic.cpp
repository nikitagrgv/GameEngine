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

	unsigned int vertex_shader = shaders_manager_.createVertexShader(vertex_shader_source);
	unsigned int fragment_shader = shaders_manager_.createFragmentShader(fragment_shader_source);
	shader_program_ = shaders_manager_.createProgram(vertex_shader, fragment_shader, true);

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

	// CONTROLS CALLBACKS
	Input::addKeyPressedCallback(GLFW_KEY_Q, [this](){
		wireframe_mode_ = !wireframe_mode_;
		std::cout << "Wireframe mode: " << wireframe_mode_ << std::endl;

		glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode_ ? GL_LINE : GL_FILL);
	});
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
	glDeleteBuffers(1, &ebo_);
}
