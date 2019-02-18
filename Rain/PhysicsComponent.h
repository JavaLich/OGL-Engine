#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "Level.h"
#include "Entity.h"
class Entity;
class PhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();
	virtual void update(Entity& entity,Level *level, double delta);
};

