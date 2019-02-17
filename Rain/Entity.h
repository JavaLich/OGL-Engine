#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Helper.h"
#include "PhysicsComponent.h"
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
	uint32_t meshID;
	bool ticks = true;
	void setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	PhysicsComponent* physics;

};

