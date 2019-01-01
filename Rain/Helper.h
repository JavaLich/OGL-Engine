#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <stb_image.h>

#include <math.h>
#include <string>
#include <iostream>
#include <vector>

#include "Model.h"

#define PI 3.1415

class Helper
{
public:
	Helper();
	~Helper();
	
	static glm::mat4 createTransformationMatrix(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale);
	static glm::mat4 createTransformationMatrix(glm::mat4 matrix, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale);
	static int fastFloor(double x);
	static double dot(double gx, double gy, double x, double y);
	static float interpolate(float a, float b, float blend);
	static void printVec3(glm::vec3 vector);
	static GLuint getTextureFromFile(const char * path, const std::string & directory, bool gamma = false);

};

