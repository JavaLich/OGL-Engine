#pragma once
#include "glm.hpp"
#include "Entity.h"
class Entity;
class RotatingComponent
{
public:
	RotatingComponent(glm::vec3 rot);
	RotatingComponent();
	~RotatingComponent();
	glm::vec3 rotation;
	virtual void update(Entity& entity, double delta);
};

