#pragma once
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Cube.h"

class Engine
{
public:
    Engine(int argc, char** argv);
    void run();

private:
    static Engine* instance;

    static void displayCallback();
    static void reshapeCallback(int w, int h);
    static void keyboardCallback(unsigned char key, int x, int y);
    static void idleCallback();

    void display();
    void reshape(int w, int h);
    void keyboard(unsigned char key);
    void idle();

    Camera camera;
    Cube cube;

    float angle;
    bool perspective;
};
