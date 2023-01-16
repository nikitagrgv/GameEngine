#include "ExampleGameLogic.h"

#include "Engine.h"
#include "FileManager.h"
#include "Input.h"
#include "Render.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

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
    array_buffer_ = std::make_unique<VertexArray>();
    array_buffer_->bind();
    GL_CHECK_ERROR();

    index_buffer_ = std::make_unique<IndexBuffer>(indices_, 6);
    vertex_buffer_ = std::make_unique<VertexBuffer>(vertices_, sizeof(vertices_));
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(3); // color
    layout.push<float>(2); // texture coordinates
    array_buffer_->addBuffer(*vertex_buffer_.get(), layout);

	// ------------------------- TEXTURE1 ------------------
	stbi_set_flip_vertically_on_load(true);
	{
		glGenTextures(1, &texture_);
		glBindTexture(GL_TEXTURE_2D, texture_);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width;
		int height;
		int number_channels;
		const char *filename = "../data/textures/container.jpg";
		unsigned char *data = stbi_load(filename, &width, &height, &number_channels, 0);
		assert(data != nullptr);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// ------------------------- TEXTURE2 ------------------
	{
		glGenTextures(1, &texture2_);
		glBindTexture(GL_TEXTURE_2D, texture2_);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width;
		int height;
		int number_channels;
		const char *filename = "../data/textures/awesomeface.png";
		unsigned char *data = stbi_load(filename, &width, &height, &number_channels, 0);
		assert(data != nullptr);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

		glGenerateMipmap(GL_TEXTURE_2D);
	}


    array_buffer_->unbind();
}

void ExampleGameLogic::render()
{
	int uniform_time_location = glGetUniformLocation(shader_program_, "time");
	int uniform_texture1_location = glGetUniformLocation(shader_program_, "ourTexture");
	int uniform_texture2_location = glGetUniformLocation(shader_program_, "ourTexture2");

	glUseProgram(shader_program_);

	if (uniform_time_location != -1)
		glUniform1f(uniform_time_location, (float)Engine::getTime());
	if (uniform_texture1_location != -1)
		glUniform1i(uniform_texture1_location, 0);
	if (uniform_texture2_location != -1)
		glUniform1i(uniform_texture2_location, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2_);

    array_buffer_->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    GL_CHECK_ERROR();
}

void ExampleGameLogic::update()
{
	if (Input::isKeyDown(GLFW_KEY_ESCAPE))
		Engine::shutdownLater();
}

void ExampleGameLogic::shutdown()
{
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
