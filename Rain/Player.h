#pragma once
#include "Entity.h"
#include "View.h"
#include "Physics.h"
#include "Level.h"
#include "InputComponent.h"

#include <iostream>
class InputComponent;
class Player :
	public Entity
{
public:
	Player(View *v);
	~Player(); 
	void update(double delta, GLFWwindow*window, Level* level);
	glm::mat4 transform;
	float speed = 0.0f;
	uint32_t meshID;
	bool ticks = true;
	bool wantsToJump = false;
	View* view;
	InputComponent *input;
	
};

