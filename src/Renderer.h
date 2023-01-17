#pragma once

// clang-format off
#include <glad/glad.h>
// clang-format on

#include <iostream>

#define GL_CHECK_ERROR()                                                                           \
    while (GLenum error = glGetError())                                                            \
    {                                                                                              \
        std::cout << "OpenGL error: " << error << std::endl;                                       \
    }

class Renderer
{    
public:
    Renderer();
    ~Renderer();

private:

};


