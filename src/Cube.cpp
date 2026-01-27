#include "Cube.h"
#include <cstring>
#include <cmath>

static void normalize(float v[3])
{
    float len = std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= len;
    v[1] /= len;
    v[2] /= len;
}

Cube::Cube()
{
    float v[8][3] = {
        {-20,-20,-20},
        { 20,-20,-20},
        { 20, 20,-20},
        {-20, 20,-20},
        {-20,-20, 20},
        { 20,-20, 20},
        { 20, 20, 20},
        {-20, 20, 20}
    };
    memcpy(vertices, v, sizeof(v));

    unsigned int i[36] = {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        0,4,7, 7,3,0,
        1,5,6, 6,2,1,
        3,2,6, 6,7,3,
        0,1,5, 5,4,0
    };
    memcpy(indices, i, sizeof(i));

    // 🔴 NORMALNE PER-WIERZCHOŁEK
    for (int i = 0; i < 8; i++)
    {
        normals[i][0] = vertices[i][0];
        normals[i][1] = vertices[i][1];
        normals[i][2] = vertices[i][2];
        normalize(normals[i]);
    }
}

void Cube::draw()
{
    GLfloat matDiff[] = { 0.8f, 0.2f, 0.2f, 1.0f };
    GLfloat matSpec[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMateriali(GL_FRONT, GL_SHININESS, 64);

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < 36; i++)
    {
        unsigned int idx = indices[i];
        glNormal3fv(normals[idx]);     // 🔴 różna normalna
        glVertex3fv(vertices[idx]);
    }

    glEnd();
}
