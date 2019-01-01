#pragma once

#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>

#include "MasterRenderer.h"
#include "Entity.h"
#include "Scene.h"
#include "Player.h"

#include <iostream>
#include <stdio.h>  
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <random>

const int UPS = 60;
const int TARGET_FPS = 60;


class Game
{
public:
	Game();
	~Game();
	void loop();
	void render();
	void update(double delta);
	void process();
	void cleanup();

	GLFWwindow* window;
	MasterRenderer renderer;
	Scene *scene;
	Terrain *terrain;
	WaterTile *water;
	Player* player;
	static int width, height;
};

