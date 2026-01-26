#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera();
    glm::mat4 getView() const;

    void moveForward(float d);
    void moveRight(float d);

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
};
