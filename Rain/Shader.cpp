 #include "Shader.h"



Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* tcsPath, const char* tesPath) : vPath(vertexPath),fPath(fragmentPath),csPath(tcsPath),esPath(tesPath)
{

	std::string vertexCode;
	std::string fragmentCode;
	std::string tcsCode;
	std::string tesCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream tcsFile;
	std::ifstream tesFile;
	vShaderFile.exceptions(std::fstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::fstream::failbit | std::ifstream::badbit);
	tcsFile.exceptions(std::fstream::failbit | std::ifstream::badbit);
	tesFile.exceptions(std::fstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		tcsFile.open(tcsPath);
		tesFile.open(tesPath);
		std::stringstream vShaderStream, fShaderStream, tcsStream, tesStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		tcsStream << tcsFile.rdbuf();
		tesStream << tesFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		tcsFile.close();
		tesFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		tesCode = tesStream.str();
		tcsCode = tcsStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Couldn't read shader file: " << vertexPath << " and: " << fragmentPath << " and: " << tcsPath << " and: " << tesPath<< std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* controlCode = tcsCode.c_str();
	const char* evaluationCode = tesCode.c_str();
	

	unsigned int vertex, fragment, control, evaluation;
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

	control = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(control, 1, &controlCode, NULL);
	glCompileShader(control);

	glGetShaderiv(control, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(control, 512, NULL, infoLog);
		std::cout << "Tesselation control shader failed to compile: \n" << infoLog << std::endl;
	}

	evaluation = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(evaluation, 1, &evaluationCode, NULL);
	glCompileShader(evaluation);

	glGetShaderiv(evaluation, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(evaluation, 512, NULL, infoLog);
		std::cout << "Tesselation evaluation shader failed to compile: \n" << infoLog << std::endl;
	}

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glAttachShader(shaderID, control);
	glAttachShader(shaderID, evaluation);
	glLinkProgram(shaderID);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "Failed link shader: \n" << infoLog << std::endl;
	}

	glValidateProgram(shaderID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(control);
	glDeleteShader(evaluation);
}

void Shader::reload() {
	glDeleteShader(shaderID);
	const char* vertexPath = vPath;
	const char* fragmentPath = fPath;
	const char* tcsPath = csPath;
	const char* tesPath = esPath;

	std::string vertexCode;
	std::string fragmentCode;
	std::string tcsCode;
	std::string tesCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream tcsFile;
	std::ifstream tesFile;
	vShaderFile.exceptions(std::fstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::fstream::failbit | std::ifstream::badbit);
	tcsFile.exceptions(std::fstream::failbit | std::ifstream::badbit);
	tesFile.exceptions(std::fstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		tcsFile.open(tcsPath);
		tesFile.open(tesPath);
		std::stringstream vShaderStream, fShaderStream, tcsStream, tesStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		tcsStream << tcsFile.rdbuf();
		tesStream << tesFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		tcsFile.close();
		tesFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		tesCode = tesStream.str();
		tcsCode = tcsStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Couldn't read shader file: " << vertexPath << " and: " << fragmentPath << " and: " << tcsPath << " and: " << tesPath << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* controlCode = tcsCode.c_str();
	const char* evaluationCode = tesCode.c_str();


	unsigned int vertex, fragment, control, evaluation;
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

	control = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(control, 1, &controlCode, NULL);
	glCompileShader(control);

	glGetShaderiv(control, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(control, 512, NULL, infoLog);
		std::cout << "Tesselation control shader failed to compile: \n" << infoLog << std::endl;
	}

	evaluation = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(evaluation, 1, &evaluationCode, NULL);
	glCompileShader(evaluation);

	glGetShaderiv(evaluation, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(evaluation, 512, NULL, infoLog);
		std::cout << "Tesselation evaluation shader failed to compile: \n" << infoLog << std::endl;
	}

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glAttachShader(shaderID, control);
	glAttachShader(shaderID, evaluation);
	glLinkProgram(shaderID);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "Failed link shader: \n" << infoLog << std::endl;
	}

	glValidateProgram(shaderID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(control);
	glDeleteShader(evaluation);
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
