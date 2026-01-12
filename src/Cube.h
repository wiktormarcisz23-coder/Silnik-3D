#pragma once
#include <GL/freeglut.h>

class Cube
{
public:
    Cube();
    void draw();

private:
    float vertices[8][3];
    unsigned int indices[36];
    float colors[8][3];
};
