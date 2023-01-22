#include "Camera.h"

#include "MathUtils.h"

Camera::Camera(float fov, float aspect, float z_near, float z_far)
{
    setPerspectiveProjection(fov, aspect, z_near, z_far);
    update_all_matrices();
}

void Camera::update_all_matrices()
{
    update_transform();
    update_view_matrix();
}

// TODO optimize
void Camera::update_transform()
{
    using namespace glm;

    const mat4 matrix_rotate_pitch = rotate(mat4(1), pitch_, Math::VEC_RIGHT);
    const mat4 matrix_rotate_yaw = rotate(mat4(1), yaw_, Math::VEC_UP);

    const mat4 matrix_translate = translate(mat4(1), position_);

    transform_ = matrix_translate * matrix_rotate_yaw * matrix_rotate_pitch;
}

void Camera::update_view_matrix()
{
    view_matrix_ = glm::inverse(transform_);
}

void Camera::setPerspectiveProjection(float fov, float aspect, float z_near, float z_far)
{
    projection_ = glm::perspective(fov, aspect, z_near, z_far);
}
