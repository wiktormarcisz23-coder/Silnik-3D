#include <GL/glew.h>
#include "Engine.h"
#include <cstdlib>

Engine* Engine::instance = nullptr;

Engine::Engine(int argc, char** argv, int w, int h, const char* t)
	: width(w), height(h),
	angle(0.0f),
	lightPos(100.0f, 100.0f, 200.0f),
	shader(nullptr)
{
	instance = this;
	glutInit(&argc, argv);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(t);
	glutIgnoreKeyRepeat(1);
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::exit(1);
	}
	lastTime = glutGet(GLUT_ELAPSED_TIME);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	shader = new Shader("vertex.glsl", "fragment.glsl");
	cube = new Cube("texture.jpg");
	objects.push_back(cube);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutKeyboardFunc(keyboardCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutIdleFunc(idleCallback);
}

Engine::~Engine()
{
	delete shader;
	for (auto obj : objects) delete obj;
}

void Engine::run()
{
	glutMainLoop();
}

void Engine::displayCallback()
{
	if (instance) instance->display();
}

void Engine::reshapeCallback(int w, int h)
{
	if (instance) instance->reshape(w, h);
}

void Engine::keyboardCallback(unsigned char key, int x, int y)
{
	if (instance) instance->keyboard(key);
}

void Engine::keyboardUpCallback(unsigned char key, int x, int y)
{
	if (instance) instance->keyboardUp(key);
}

void Engine::idleCallback()
{
	if (instance) instance->idle();
}

void Engine::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->use();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 1000.0f);
	shader->setMat4("projection", projection);
	shader->setMat4("view", camera.getView());
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", camera.getPosition());

	for (auto obj : objects)
	{
		obj->setRotation(glm::vec3(0.0f, angle, 0.0f));
		shader->setMat4("model", obj->getModelMatrix());
		obj->draw();
	}

	glutSwapBuffers();
}
void Engine::reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
	glutPostRedisplay();
}

void Engine::keyboard(unsigned char key)
{
	key = std::tolower(key);
	keys[key] = true;
	switch (key)
	{
		case 27: exit(0); break;
	}
	glutPostRedisplay();
}

void Engine::keyboardUp(unsigned char key)
{
	keys[std::tolower(key)] = false;
}

void Engine::idle()
{
	unsigned int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
	angle += rotationSpeed * deltaTime;

	if (angle >= 360.0f) angle -= 360.0f;
	if (keys['d']) camera.moveRight(-moveSpeed * deltaTime);
	if (keys['a']) camera.moveRight(moveSpeed * deltaTime);
	if (keys['s']) camera.moveUp(moveSpeed * deltaTime);
	if (keys['w']) camera.moveUp(-moveSpeed * deltaTime);

	if (cube)
	{
		glm::vec3 currentScale = cube->getScale();

		if (keys['+'] || keys['='])
		{
			currentScale += glm::vec3(scaleSpeed * deltaTime);
		}

		if (keys['-'] || keys['_'])
		{
			currentScale -= glm::vec3(scaleSpeed * deltaTime);
			currentScale = glm::max(currentScale, glm::vec3(0.2f));
		}

		cube->setScale(currentScale);
	}
	glutPostRedisplay();
}