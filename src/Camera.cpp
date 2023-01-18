#include "Camera.h"

#include "MathUtils.h"

Camera::Camera(float fov, float aspect, float z_near, float z_far)
{
    setProjection(fov, aspect, z_near, z_far);
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

    const mat4 matrix_rotate_pitch = rotate(mat4(1), pitch_, vec_right);
    const mat4 matrix_rotate_yaw = rotate(mat4(1), yaw_, vec_up);
    const mat4 matrix_rotate_roll = rotate(mat4(1), roll_, vec_forward);

    const mat4 matrix_translate = translate(mat4(1), position_);

    transform_ = matrix_translate * matrix_rotate_roll * matrix_rotate_pitch * matrix_rotate_yaw;
}

void Camera::update_view_matrix()
{
    view_matrix_ = glm::inverse(transform_);
}

void Camera::setProjection(float fov, float aspect, float z_near, float z_far)
{
    projection_ = glm::perspective(fov, aspect, z_near, z_far);
}
