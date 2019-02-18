#pragma once
#include "Entity.h"
#include "View.h"
#include "Physics.h"
#include "Level.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "PlayerPhysicsComponent.h"

#include <iostream>
class InputComponent;
class PlayerPhysicsComponent;

class Player :
	public Entity
{
public:
	Player(View *v);
	~Player(); 
	void update(double delta, GLFWwindow*window, Level* level);
	glm::mat4 transform;
	uint32_t meshID;
	bool ticks = true;
	bool wantsToJump = false;
	View* view;
	InputComponent *input;
	PhysicsComponent *physics_;
};

