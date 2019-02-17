#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "Player.h"
class Player;
class InputComponent
{
public:
	InputComponent();
	~InputComponent();
	virtual void update(Player& player, GLFWwindow* window, double delta);

};

