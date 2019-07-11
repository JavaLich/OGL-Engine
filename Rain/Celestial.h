#pragma once
#include <gl\glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Helper.h"

class Celestial 
{
public:
	Celestial(float r) {
		radius = r;
		position = glm::vec3(0.0f);
		rotation = glm::vec3(0.0f);
		transform = Helper::createTransformationMatrix(position, glm::vec3(0.0f), glm::vec3(1.0f));
		temperature = 5778;
		realRadius = 696100;
	}
	~Celestial();
	glm::mat4 transform;
	glm::vec3 velocity;
	glm::vec3 position;
	glm::vec3 rotation;
	float temperature;
	float radius;
	float realRadius;
	void setTransform(glm::vec3 pos, glm::vec3 rot);
	glm::vec3 getTempColorShift();
private:
};

