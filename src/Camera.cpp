#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
	: position(0.0f, 0.0f, 150.0f),
	target(0.0f, 0.0f, 0.0f),
	up(0.0f, 1.0f, 0.0f)
{
}

glm::mat4 Camera::getView() const
{
	return glm::lookAt(position, target, up);
}

glm::vec3 Camera::getPosition() const
{
	return position;
}

void Camera::moveRight(float d)
{
	glm::vec3 dir = glm::normalize(target - position);
	glm::vec3 right = glm::normalize(glm::cross(dir, up));
	position += right * d;
	target += right * d;
}

void Camera::moveUp(float d)
{
	position += up * d;
	target += up * d;
}