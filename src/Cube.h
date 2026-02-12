#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Object.h"

class Cube : public Object {
public:
	Cube(const char* texturePath);
	~Cube();
	void draw() override;
private:
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;
	GLuint textureID = 0;
	static constexpr float vertices[192] = {
	-20.0f, -20.0f, -20.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	20.0f, -20.0f, -20.0f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	20.0f,  20.0f, -20.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-20.0f,  20.0f, -20.0f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-20.0f, -20.0f,  20.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
	20.0f, -20.0f,  20.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
	20.0f,  20.0f,  20.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
	-20.0f,  20.0f,  20.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
	-20.0f, -20.0f, -20.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	20.0f, -20.0f, -20.0f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	20.0f, -20.0f,  20.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	-20.0f, -20.0f,  20.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	-20.0f,  20.0f, -20.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	20.0f,  20.0f, -20.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	20.0f,  20.0f,  20.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	-20.0f,  20.0f,  20.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	-20.0f, -20.0f, -20.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-20.0f,  20.0f, -20.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-20.0f,  20.0f,  20.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-20.0f, -20.0f,  20.0f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	20.0f, -20.0f, -20.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	20.0f,  20.0f, -20.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	20.0f,  20.0f,  20.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	20.0f, -20.0f,  20.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f
	};

	static constexpr unsigned int indices[36] = 
{
	0,1,2, 2,3,0,
	4,5,6, 6,7,4,
	8,9,10,10,11,8,
	12,13,14,14,15,12,
	16,17,18,18,19,16,
	20,21,22,22,23,20
	};
	void setupBuffers();
	void loadTexture(const char* path);
};