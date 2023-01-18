#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera(float fov, float aspect, float z_near, float z_far);

    glm::mat4 getTransform() const { return transform_; }
    glm::mat4 getView() const { return view_matrix_; }

    glm::vec3 getPosition() const { return position_; }
    void setPosition(const glm::vec3 position) { position_ = position; update_all_matrices(); }

    glm::mat4 getProjection() const { return projection_; }
    void setProjection(const glm::mat4 projection) { projection_ = projection; }
    void setProjection(float fov, float aspect, float z_near, float z_far);

    float getPitch() const { return pitch_; }
    void setPitch(float pitch) { pitch_ = pitch; update_all_matrices(); }

    float getYaw() const { return yaw_; }
    void setYaw(float yaw) { yaw_ = yaw; update_all_matrices(); }

private:
    void update_all_matrices();
    void update_transform();
    void update_view_matrix();

private:
    glm::mat4 transform_{1};
    glm::mat4 view_matrix_{1};

    glm::mat4 projection_{1};

    glm::vec3 position_{0};
    float pitch_{0};
    float yaw_{0};
};
