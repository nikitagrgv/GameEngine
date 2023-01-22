#pragma once

#include <glm/glm.hpp>

namespace Math
{

constexpr glm::vec3 VEC_UP{0.f, 1.f, 0.f};
constexpr glm::vec3 VEC_FORWARD{0.f, 0.f, -1.f};
constexpr glm::vec3 VEC_RIGHT{1.f, 0.f, 0.f};

inline glm::vec3 getUp(const glm::mat3& transform)
{
    return glm::normalize(transform[1]);
}

inline glm::vec3 getForward(const glm::mat3& transform)
{
    return glm::normalize(-transform[2]);
}

inline glm::vec3 getRight(const glm::mat3& transform)
{
    return glm::normalize(transform[0]);
}

inline glm::vec3 getUp(const glm::mat4& transform)
{
    return glm::normalize(glm::vec3(transform[1]));
}

inline glm::vec3 getForward(const glm::mat4& transform)
{
    return glm::normalize(glm::vec3(-transform[2]));
}

inline glm::vec3 getRight(const glm::mat4& transform)
{
    return glm::normalize(glm::vec3(transform[0]));
}

} // namespace Math
