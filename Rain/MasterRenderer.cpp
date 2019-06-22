#include "MasterRenderer.h"



MasterRenderer::MasterRenderer()
{
	
}


MasterRenderer::~MasterRenderer()
{
	
}

void MasterRenderer::render(Scene &scene, GLFWwindow *window)
{
/*	scene.fbos.bindReflectionBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float distance = 2*(scene.view.getPosition().y-scene.waterTiles[0].getHeight());
	scene.view.translatePosition(glm::vec3(0.0f, -distance, 0.0f));
	scene.view.invertPitch();
	scene.clipPlane = glm::vec4(0.0f, 1.0f, 0.0f, -scene.waterTiles[0].getHeight()+2.5f);
	entityRenderer.render(scene);
	terrainRenderer.render(scene);
	scene.view.translatePosition(glm::vec3(0.0f, distance, 0.0f));
	scene.view.resetViewMatrix();

	scene.fbos.bindRefractionBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.clipPlane = glm::vec4(0.0f, -1.0f, 0.0f, scene.waterTiles[0].getHeight());
	entityRenderer.render(scene);
	terrainRenderer.render(scene);

	glDisable(GL_CLIP_DISTANCE0);
	scene.clipPlane = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	scene.fbos.unbindCurrentFrameBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	entityRenderer.render(scene);
	terrainRenderer.render(scene);
	waterRenderer.render(scene);
	*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//entityRenderer.render(scene, *world);
	starRenderer.render(scene, *world);
	scene.clearEntities();
	scene.terrains.clear();
	scene.waterTiles.clear();
}

void MasterRenderer::init()
{
	waterRenderer.init();
	world = new World();
}
