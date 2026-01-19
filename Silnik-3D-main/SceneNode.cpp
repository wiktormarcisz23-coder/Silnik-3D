#include "SceneNode.h"

#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>

void SceneNode::addChild(std::unique_ptr<SceneNode> child)
{
    m_children.emplace_back(std::move(child));
}

void SceneNode::update(float dt)
{
    onUpdate(dt);
    for (auto& c : m_children)
        c->update(dt);
}

void SceneNode::applyMaterial() const
{
    // Przy włączonym GL_COLOR_MATERIAL glColor* wpływa na materiał,
    // więc ustawiamy kolor zgodnie z diffuse, żeby tryb "śledzenia kolorów"
    // miał sens.
    glColor4fv(&material.diffuse.x);

    // Lab 10: właściwości materiału ustawiane przez glMaterial*.
    glMaterialfv(GL_FRONT, GL_AMBIENT, &material.ambient.x);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &material.diffuse.x);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &material.specular.x);

    int shin = material.shininess;
    if (shin < 1) shin = 1;
    if (shin > 128) shin = 128;
    glMateriali(GL_FRONT, GL_SHININESS, shin);
}

void SceneNode::draw(const glm::mat4& view, const glm::mat4& parentModel) const
{
    const glm::mat4 model = parentModel * transform.matrix();

    // Ustawiamy macierz MODELVIEW = View * Model.
    glm::mat4 MV = view * model;
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(MV));

    applyMaterial();
    onDraw();

    for (const auto& c : m_children)
        c->draw(view, model);
}
