#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath, const char* tcsPath, const char* tesPath);
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void bind();
	void setFloat(const char* name, float value);
	void setMat4(const char* name, glm::mat4 value);
	void setInt(const char* name, int value);
	void setVec3(const char* name, glm::vec3 value);
	void setVec4(const char* name, glm::vec4 value);
	void setBool(const char* name, bool value);
	void reload();
	GLuint shaderID;
private:
	const char* vPath;
	const char* fPath;
	const char* csPath;
	const char* esPath;
};

