#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "Player.h"
class Player;
class PhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();
	virtual void update(Entity& entity, double delta);
};

