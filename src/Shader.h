#pragma once

#include "FileManager.h"

// clang-format off
#include <glad/glad.h>
// clang-format on

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <unordered_map>

class Shader
{
public:
    Shader(const std::string& filename_vertex, const std::string& filename_fragment);
    ~Shader();

    void setShaders(const std::string& filename_vertex, const std::string& filename_fragment);

    void bind() const;
    void unbind() const;

    bool isValid() const { return is_valid_; }

    int getUniformLocation(const std::string& name) const;

    template<typename T>
    void setUniform(const std::string& name, T value)
    {
        const auto location = getUniformLocation(name);

        if (location == -1)
        {
            std::cout << "Uniform not found: " << name.c_str() << std::endl;
            return;
        }

        setUniform(location, value);
    }

    // -------------------------------------------------------

    template<typename T>
    void setUniform(int location, T value)
    {
        static_assert(0 && "Invalid type");
    }

    template<>
    void setUniform<float>(int location, float value)
    {
        bind();
        glUniform1f(location, value);
    }

    template<>
    void setUniform<int>(int location, int value)
    {
        bind();
        glUniform1i(location, value);
    }

    template<>
    void setUniform<glm::vec2>(int location, glm::vec2 value)
    {
        bind();
        glUniform2f(location, value.x, value.y);
    }

    template<>
    void setUniform<glm::vec3>(int location, glm::vec3 value)
    {
        bind();
        glUniform3f(location, value.x, value.y, value.z);
    }

    template<>
    void setUniform<glm::vec4>(int location, glm::vec4 value)
    {
        bind();
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    // -------------------------------------------------------

private:
    mutable std::unordered_map<std::string, int> location_cache_;

    unsigned int program_id_{0};
    bool is_valid_{false};
};
