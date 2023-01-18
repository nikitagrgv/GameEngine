#pragma once

#include <glm/glm.hpp>

constexpr glm::vec3 vec_up{0.f, 1.f, 0.f};
constexpr glm::vec3 vec_forward{0.f, 0.f, -1.f};
constexpr glm::vec3 vec_right{1.f, 0.f, 0.f};


// TODO optimize

inline glm::vec3 getUp(const glm::mat3& transform)
{
    return transform * vec_up;
}

inline glm::vec3 getForward(const glm::mat3& transform)
{
    return transform * vec_forward;
}

inline glm::vec3 getRight(const glm::mat3& transform)
{
    return transform * vec_right;
}

inline glm::vec3 getUp(const glm::mat4& transform)
{
    return getUp(glm::mat3(transform));
}

inline glm::vec3 getForward(const glm::mat4& transform)
{
    return getForward(glm::mat3(transform));
}

inline glm::vec3 getRight(const glm::mat4& transform)
{
    return getRight(glm::mat3(transform));
}

