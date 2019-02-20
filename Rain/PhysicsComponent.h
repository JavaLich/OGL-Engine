#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "Level.h"
#include "Entity.h"
#include "Physics.h"
class Entity;
class Level;
class PhysicsComponent
{
public:
	PhysicsComponent();
	PhysicsComponent(glm::vec3 l);
	~PhysicsComponent();
	virtual void update(Entity& entity,Level &level, double delta);
	Physics* physics;
	glm::vec3 volume;
};

