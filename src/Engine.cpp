#include "Engine.h"
#include <cstdlib>
#include <cctype>

Engine* Engine::instance = nullptr;

Engine::Engine(int argc, char** argv)
    : angle(0.0f),
    lookA(20.0f),
    width(800),
    height(600),
    lightPos(200.0f, 200.0f, 200.0f),
    smoothShading(true)
{
    instance = this;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("LAB 9 + LAB 10 – Transformacje i oswietlenie");

    glEnable(GL_DEPTH_TEST);

    // ===== LAB 10 – OŚWIETLENIE =====
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    GLfloat ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    // Spotlight (Warna)
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 15.0f);

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

    glShadeModel(smoothShading ? GL_SMOOTH : GL_FLAT);

    // ===== PROJECTION (LAB 9) =====
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 P = glm::perspective(
        glm::radians(50.0f),
        (float)width / height,
        130.0f,
        470.0f
    );
    glLoadMatrixf(glm::value_ptr(P));

    // ===== VIEW – OBSERWATOR =====
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(camera.getView()));

    // ===== ŚWIATŁO (LAB 10) =====
    GLfloat pos[] = { lightPos.x, lightPos.y, lightPos.z, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    GLfloat dir[] = { -pos[0], -pos[1], -pos[2] };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

    // ===== MACIERZ SCENY (LAB 9) =====
    glm::mat4 MatM(1.0f);
    MatM = glm::translate(MatM, glm::vec3(0.0f, 0.0f, -300.0f));
    MatM = glm::rotate(MatM, glm::radians(lookA), glm::vec3(1, 0, 0));
    MatM = glm::rotate(MatM, glm::radians(angle), glm::vec3(0, 1, 0));

    glm::mat4 MatRot120 = glm::rotate(
        glm::mat4(1.0f),
        glm::radians(120.0f),
        glm::vec3(0, 1, 0)
    );
    glm::mat4 MatTra100 = glm::translate(
        glm::mat4(1.0f),
        glm::vec3(100.0f, 0, 0)
    );

    // ===== OBIEKTY =====
    glLoadMatrixf(glm::value_ptr(MatM * MatTra100));
    glColor3f(0, 1, 0);
    glutSolidCube(50);

    glLoadMatrixf(glm::value_ptr(MatM * MatRot120 * MatTra100));
    glColor3f(1, 1, 0);
    glutSolidTeapot(40);

    glLoadMatrixf(glm::value_ptr(MatM * MatRot120 * MatRot120 * MatTra100));
    glColor3f(0, 0, 1);
    glutSolidSphere(50, 20, 20);

    glutSwapBuffers();
}

void Engine::reshape(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
}

void Engine::keyboard(unsigned char key)
{
    key = (unsigned char)std::tolower(key);

    switch (key)
    {
    case 27: exit(0);
    case 'c': smoothShading = !smoothShading; break;

        // sterowanie spotlightem
    case 'w': lightPos.z -= 20; break;
    case 's': lightPos.z += 20; break;
    case 'a': lightPos.x -= 20; break;
    case 'd': lightPos.x += 20; break;
    case 'q': lightPos.y += 20; break;
    case 'e': lightPos.y -= 20; break;
    }
}

void Engine::idle()
{
    angle += 0.2f;
    if (angle > 360.0f) angle -= 360.0f;

    glutPostRedisplay();
}
