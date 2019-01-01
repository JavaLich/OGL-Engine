#include "Helper.h"



Helper::Helper()
{

}


Helper::~Helper()
{
}

glm::mat4 Helper::createTransformationMatrix(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale)
{
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, translate);
	matrix = glm::rotate(matrix, rotate.x, glm::vec3(1.0f, 0.0, 0.0));
	matrix = glm::rotate(matrix, rotate.y, glm::vec3(0.0f, 1.0f, 0.0));
	matrix = glm::rotate(matrix, rotate.z, glm::vec3(0.0f, 0.0, 1.0f));
	matrix = glm::scale(matrix, scale);
	return matrix;
}

glm::mat4 Helper::createTransformationMatrix(glm::mat4 matrix, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale)
{
	matrix = glm::translate(matrix, translate);
	matrix = glm::rotate(matrix, rotate.x, glm::vec3(1.0f, 0.0, 0.0));
	matrix = glm::rotate(matrix, rotate.y, glm::vec3(0.0f, 1.0f, 0.0));
	matrix = glm::rotate(matrix, rotate.z, glm::vec3(0.0f, 0.0, 1.0f));
	matrix = glm::scale(matrix, scale);
	return matrix;
}

int Helper::fastFloor(double x)
{
	return x>0 ? (int)x : (int)x - 1;
}

double Helper::dot(double gx, double gy, double x, double y)
{
	return gx*x + gy*y;
}

float Helper::interpolate(float a, float b, float blend)
{
	double theta = blend * PI;
	float f = (float)(1.0f - cosf(theta))*0.5f;
	return a * (1.0f - f) + b * f;
}

void Helper::printVec3(glm::vec3 vector)
{
	std::cout << "X: " << vector.x << ", Y: " << vector.y << ", Z: " << vector.z << std::endl;
}

GLuint Helper::getTextureFromFile(const char * path, const std::string & directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}