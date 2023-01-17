#pragma once

#include "FileManager.h"

#include <glm/vec2.hpp>
#include <string>

class Shader
{
public:
    Shader(const std::string& filename_vertex, const std::string& filename_fragment);
    ~Shader();

    void setShaders(const std::string& filename_vertex, const std::string& filename_fragment);

    void bind() const;
    void unbind() const;

    bool isValid() const { return is_valid_; }

    template<typename T>
    void setUniform(const std::string& name, T value)
    {
        static_assert(0 && "Invalid type");
    }

    template<>
    void setUniform<float>(const std::string& name, float value)
    {}

private:
    unsigned int getUniformLocation(const std::string& name);

private:
    unsigned int program_id_{0};
    bool is_valid_{false};
};
