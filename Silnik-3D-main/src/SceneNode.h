#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <vector>

// Lab 9 (zad. 2): prosta hierarchia obiektów gry.
// Każdy węzeł ma Transform + Material i może mieć dzieci.

struct Transform
{
    glm::vec3 position{0.0f};
    glm::vec3 rotationDeg{0.0f}; // Euler (X,Y,Z) w stopniach
    glm::vec3 scale{1.0f, 1.0f, 1.0f};

    glm::mat4 matrix() const
    {
        glm::mat4 M(1.0f);
        M = glm::translate(M, position);
        M = glm::rotate(M, glm::radians(rotationDeg.x), glm::vec3(1, 0, 0));
        M = glm::rotate(M, glm::radians(rotationDeg.y), glm::vec3(0, 1, 0));
        M = glm::rotate(M, glm::radians(rotationDeg.z), glm::vec3(0, 0, 1));
        M = glm::scale(M, scale);
        return M;
    }
};

struct Material
{
    glm::vec4 ambient{0.2f, 0.2f, 0.2f, 1.0f};
    glm::vec4 diffuse{0.8f, 0.8f, 0.8f, 1.0f};
    glm::vec4 specular{0.9f, 0.9f, 0.9f, 1.0f};
    int shininess{64}; // 1..128
};

class SceneNode
{
public:
    virtual ~SceneNode() = default;

    Transform transform;
    Material material;

    void addChild(std::unique_ptr<SceneNode> child);

    // update/draw z uwzględnieniem hierarchii
    void update(float dt);
    void draw(const glm::mat4& view, const glm::mat4& parentModel = glm::mat4(1.0f)) const;

protected:
    virtual void onUpdate(float /*dt*/) {}
    virtual void onDraw() const = 0;

    void applyMaterial() const;

private:
    std::vector<std::unique_ptr<SceneNode>> m_children;
};
