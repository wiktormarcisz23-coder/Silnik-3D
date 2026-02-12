#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
private:
	GLuint ID;
	void checkCompileErrors(GLuint shader, std::string type);
};