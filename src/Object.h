#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Object {

public:
	Object();
	virtual ~Object() = default;
	virtual void draw() = 0;
	void setPosition(const glm::vec3& pos);
	void setRotation(const glm::vec3& rot);
	void setScale(const glm::vec3& scl);
	glm::mat4 getModelMatrix() const;
	glm::vec3 getScale() const { return scale; }

protected:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};