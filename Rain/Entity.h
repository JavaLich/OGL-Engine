#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Helper.h"
#include "Model.h"

#include <iostream>
#include <vector>
class PhysicsComponent;
class Level;
class Entity
{
public:
	Entity(int meshID, PhysicsComponent* physicsComponent);
	~Entity();
	virtual void update(Level &level, double delta);
	glm::mat4 transform;
	glm::vec3 velocity;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	float speed = 2.0f;
	uint32_t meshID;
	bool ticks = true;
	bool gravity = true;
	void setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	PhysicsComponent* physics_;

};

