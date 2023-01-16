#pragma once

#include "GameLogic.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <memory>

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
	std::unique_ptr<IndexBuffer> index_buffer_;
	std::unique_ptr<VertexBuffer> vertex_buffer_;
	std::unique_ptr<VertexArray> array_buffer_;

	std::unique_ptr<Shader> shader_;

	bool wireframe_mode_ = false;

	unsigned int texture_;
	unsigned int texture2_;

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texture_coordinates;
	};

	const Vertex vertices_[4]{
		{  {0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // top right
		{ {0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // bottom right
		{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // bottom left
		{ {-0.5f, 0.5f, 0.0f}, {0.8f, 0.1f, 0.8f}, {0.0f, 1.0f}}  // top left
	};

	const unsigned int indices_[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
};
