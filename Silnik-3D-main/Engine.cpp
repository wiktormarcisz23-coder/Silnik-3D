#include "Engine.h"

Engine* Engine::instance = nullptr;

Engine::Engine(int argc, char** argv)
    : angle(0.0f), perspective(true)
{
    instance = this;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Labs");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutIdleFunc(idleCallback);
}

void Engine::run()
{
    glutMainLoop();
}

void Engine::displayCallback() { instance->display(); }
void Engine::reshapeCallback(int w, int h) { instance->reshape(w, h); }
void Engine::keyboardCallback(unsigned char key, int, int) { instance->keyboard(key); }
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

    glm::mat4 M = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0));
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
    if (key == 27) exit(0);
    if (key == 'p') perspective = !perspective;
}

void Engine::idle()
{
    angle += 0.1f;
    glutPostRedisplay();
}
