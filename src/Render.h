#pragma once

#include <glad/glad.h>

#include <iostream>

#define GL_CHECK_ERROR()                                                                           \
	while (GLenum error = glGetError())                                                            \
	{                                                                                              \
		std::cout << "OpenGL error: " << error << std::endl;                                       \
	}
