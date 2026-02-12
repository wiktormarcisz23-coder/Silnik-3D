#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Camera.h"
#include "Shader.h"
#include "Object.h"
#include "Cube.h"

class Engine
{
public:
	Engine(int argc, char** argv, int width = 800, int height = 600, const char* title = "3D Engine");
	~Engine();
	void run();

private:
	static Engine* instance;
	static void displayCallback();
	static void reshapeCallback(int w, int h);
	static void keyboardCallback(unsigned char key, int x, int y);
	static void keyboardUpCallback(unsigned char key, int x, int y);
	static void idleCallback();
	void display();
	void reshape(int w, int h);
	void keyboard(unsigned char key);
	void keyboardUp(unsigned char key);
	void idle();
	Camera camera;
	Shader* shader = nullptr;
	std::vector<Object*> objects;
	Cube* cube = nullptr;
	glm::vec3 lightPos;
	int width, height;
	float angle;
	unsigned int lastTime = 0;
	float rotationSpeed = 40.0f;
	float moveSpeed = 40.0f;
	float scaleSpeed = 1.0f;
	bool keys[256] = { false };
};