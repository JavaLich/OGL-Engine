#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Helper.h"
#include "Physics.h"
#include "Model.h"


#include <iostream>
#include <vector>
class Entity
{
public:
	Entity(int meshID);
	~Entity();
	virtual void update(double delta);
	glm::mat4 transform;
	glm::vec3 velocity;
	glm::vec3 position;
	float speed = 2.0f;
	uint32_t meshID;
	bool ticks = true;
	void setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	Physics* physics;
};

