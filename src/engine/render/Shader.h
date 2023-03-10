#pragma once

#include "engine/core/FileManager.h"
#include "engine/core/Object.h"
#include "engine/core/SharedPtr.h"

// clang-format off
#include "glad/glad.h"
// clang-format on

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

class Shader;
using ShaderPtr = SharedPtr<Shader>;

class Shader final : public Object
{
public:
    static ShaderPtr create(const std::string& filename_vertex, const std::string& filename_fragment);

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void setShaders(const std::string& filename_vertex, const std::string& filename_fragment);

    void bind() const;
    void unbind() const;

    bool isValid() const { return program_id_ != 0; }

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

        setUniform<T>(location, value);
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
    void setUniform(int location, const glm::vec2& value)
    {
        bind();
        glUniform2f(location, value.x, value.y);
    }

    template<>
    void setUniform(int location, const glm::vec3& value)
    {
        bind();
        glUniform3f(location, value.x, value.y, value.z);
    }

    template<>
    void setUniform(int location, const glm::vec4& value)
    {
        bind();
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    template<>
    void setUniform(int location, const glm::mat3& value)
    {
        bind();
        glUniformMatrix3fv(location, 1, false, glm::value_ptr(value));
    }

    template<>
    void setUniform(int location, const glm::mat4& value)
    {
        bind();
        glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
    }

private:
    Shader(const std::string& filename_vertex, const std::string& filename_fragment);
    ~Shader() override;

private:
    mutable std::unordered_map<std::string, int> location_cache_;

    unsigned int program_id_{0};
};
