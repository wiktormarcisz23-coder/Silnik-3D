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
