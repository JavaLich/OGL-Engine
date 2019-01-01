#include "Shader.h"



Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::fstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::fstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Couldn't read shader file: " << vertexPath << " and: " << fragmentPath << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Vertex shader failed to compile: \n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Fragment shader failed to compile: \n" << infoLog << std::endl;
	}
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glLinkProgram(shaderID);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "Failed link shader: \n" << infoLog << std::endl;
	}

	glValidateProgram(shaderID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
}

void Shader::bind()
{
	glUseProgram(shaderID);
}

void Shader::setFloat(const char * name, float value)
{
	glUniform1f(glGetUniformLocation(shaderID, name), value);
}

void Shader::setMat4(const char * name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, &value[0][0]);
}

void Shader::setInt(const char * name, int value)
{
	glUniform1i(glGetUniformLocation(shaderID, name), value);
}

void Shader::setVec3(const char * name, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(shaderID, name), value.x, value.y, value.z);
}

void Shader::setVec4(const char * name, glm::vec4 value)
{
	glUniform4f(glGetUniformLocation(shaderID, name), value.x, value.y, value.z, value.w);
}

void Shader::setBool(const char * name, bool value)
{
	glUniform1i(glGetUniformLocation(shaderID, name), value);
}
