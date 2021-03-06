#pragma once
#include <glm.hpp>
#include <iostream>
#include "Helper.h"
class Physics
{
public:
	Physics(glm::vec3 &p, glm::vec3 &v, glm::vec3 l);
	Physics();
	~Physics();
	
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 length = glm::vec3(0.0f);
	bool intersects(glm::vec3 p, glm::vec3 l);
};

