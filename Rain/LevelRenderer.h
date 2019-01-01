#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>


#include "Scene.h"
#include "Model.h"
#include "Mesh.h"
#include "World.h"
#include "Helper.h"

class LevelRenderer
{
public:
	LevelRenderer();
	~LevelRenderer();
	void render(Scene &scene, World world);
};

