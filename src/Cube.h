#pragma once
#include <GL/freeglut.h>

class Cube
{
public:
    Cube();
    void draw();

private:
    float vertices[8][3];
    float normals[8][3];        // 🔴 per-wierzchołek
    unsigned int indices[36];
};
