#include "Engine.h"
#include <cstdlib>

Engine* Engine::instance = nullptr;

Engine::Engine(int argc, char** argv)
    : angleX(0.0f), angleY(0.0f), perspective(true)
{
    instance = this;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL WASD + Arrows");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialCallback);
    glutIdleFunc(idleCallback);
}

void Engine::run()
{
    glutMainLoop();
}

void Engine::displayCallback() { instance->display(); }
void Engine::reshapeCallback(int w, int h) { instance->reshape(w, h); }
void Engine::keyboardCallback(unsigned char key, int, int) { instance->keyboard(key); }
void Engine::specialCallback(int key, int, int) { instance->special(key); }
void Engine::idleCallback() { instance->idle(); }

void Engine::display()
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (perspective)
    {
        glm::mat4 P = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 1.0f, 500.0f);
        glLoadMatrixf(glm::value_ptr(P));
    }
    else
    {
        glm::mat4 P = glm::ortho(-50.f, 50.f, -50.f, 50.f, 1.f, 500.f);
        glLoadMatrixf(glm::value_ptr(P));
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(camera.getView()));

    glm::mat4 M(1.0f);
    M = glm::rotate(M, glm::radians(angleX), glm::vec3(1, 0, 0));
    M = glm::rotate(M, glm::radians(angleY), glm::vec3(0, 1, 0));
    glMultMatrixf(glm::value_ptr(M));

    cube.draw();
    glutSwapBuffers();
}

void Engine::reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Engine::keyboard(unsigned char key)
{
    const float speed = 2.0f;

    switch (key)
    {
    case 27: exit(0);
    case 'p': perspective = !perspective; break;

    case 'w': camera.moveForward(speed); break;
    case 's': camera.moveForward(-speed); break;
    case 'a': camera.moveRight(-speed); break;
    case 'd': camera.moveRight(speed); break;
    }
}

void Engine::special(int key)
{
    const float rotSpeed = 2.0f;

    switch (key)
    {
    case GLUT_KEY_LEFT:  angleY -= rotSpeed; break;
    case GLUT_KEY_RIGHT: angleY += rotSpeed; break;
    case GLUT_KEY_UP:    angleX -= rotSpeed; break;
    case GLUT_KEY_DOWN:  angleX += rotSpeed; break;
    }
}

void Engine::idle()
{
    glutPostRedisplay();
}
