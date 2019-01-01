#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Component.h"
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
	void attachComponent(Component comp);
	glm::mat4 transform;
	uint32_t meshID;
	bool ticks = true;
	std::vector<Component> components;
	void setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	PhysicsComponent* physics;

};

