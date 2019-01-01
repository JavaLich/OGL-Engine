#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>


#include "Scene.h"
#include "Model.h"
#include "Mesh.h"
#include "Helper.h"
#include "World.h"

class WaterRenderer
{
public:
	WaterRenderer();
	~WaterRenderer();
	void init();
	void render(Scene& scene, World world);
	GLuint dudvMap;
	GLuint normalMap;
};

