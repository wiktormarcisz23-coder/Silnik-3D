#include "Object.h"

Object::Object() : position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}

void Object::setPosition(const glm::vec3& pos) { position = pos; }
void Object::setRotation(const glm::vec3& rot) { rotation = rot; }
void Object::setScale(const glm::vec3& scl) { scale = scl; }

glm::mat4 Object::getModelMatrix() const
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, scale);
	return model;
}