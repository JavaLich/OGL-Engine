#pragma once
#include "Entity.h"
#include "View.h"
#include "PhysicsComponent.h"
#include "Level.h"

#include <iostream>
class Player :
	public Entity
{
public:
	Player(View *v);
	~Player();
	void update(double delta, GLFWwindow *window, Level* level);
	glm::mat4 transform;
	glm::vec3 velocity;
	glm::vec3 position;
	float speed = 0.0f;
	uint32_t meshID;
	bool ticks = true;
	View* view;
	
};

