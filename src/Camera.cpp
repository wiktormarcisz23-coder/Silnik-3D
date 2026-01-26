#include "Camera.h"

Camera::Camera()
{
    position = glm::vec3(0, 0, 150);
    target = glm::vec3(0, 0, 0);
    up = glm::vec3(0, 1, 0);
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(position, target, up);
}

void Camera::moveForward(float d)
{
    glm::vec3 dir = glm::normalize(target - position);
    position += dir * d;
    target += dir * d;
}

void Camera::moveRight(float d)
{
    glm::vec3 dir = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(dir, up));
    position += right * d;
    target += right * d;
}
