#include "WaterRenderer.h"



WaterRenderer::WaterRenderer()
{
	
}


WaterRenderer::~WaterRenderer()
{
}

void WaterRenderer::init()
{
	dudvMap = Helper::getTextureFromFile("waterDUDV.png", "assets/textures");
	normalMap = Helper::getTextureFromFile("normalMap.png", "assets/textures");
}

void WaterRenderer::render(Scene & scene, World world)
{
	scene.shaders.at(WATER_SHADER).bind();
	scene.shaders.at(WATER_SHADER).setMat4("view", scene.view.getViewMatrix());
	scene.shaders.at(WATER_SHADER).setMat4("proj", scene.view.getProjection());
	scene.shaders.at(WATER_SHADER).setVec3("cameraPos", scene.view.getPosition());

	//Directional Light
	
	scene.shaders.at(SHADER).setVec3("dirLight.direction", world.levels[world.activeLevel].dirLight.direction);
	scene.shaders.at(SHADER).setVec3("dirLight.ambient", world.levels[world.activeLevel].dirLight.ambient);
	scene.shaders.at(SHADER).setVec3("dirLight.diffuse", world.levels[world.activeLevel].dirLight.diffuse);
	scene.shaders.at(SHADER).setVec3("dirLight.specular", world.levels[world.activeLevel].dirLight.specular);

	scene.shaders[WATER_SHADER].setInt("reflectionTexture", 0);
	scene.shaders[WATER_SHADER].setInt("refractionTexture", 1);
	scene.shaders[WATER_SHADER].setInt("dudvMap", 2);
	scene.shaders[WATER_SHADER].setInt("normalMap", 3);
	scene.shaders[WATER_SHADER].setInt("depthMap", 4);
	scene.shaders[WATER_SHADER].setFloat("moveFactor", scene.counter);
	scene.shaders[WATER_SHADER].setFloat("near", near);
	scene.shaders[WATER_SHADER].setFloat("far", far);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, scene.fbos.getReflectionTexture());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, scene.fbos.getRefractionTexture());

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, dudvMap);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, normalMap);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, scene.fbos.getRefractionDepthTexture());

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	int lights = world.levels[world.activeLevel].pLights.size();
	
	for (int i = 0; i < lights; i++) {
		scene.loadPointLight(world.levels[world.activeLevel].pLights.at(i), i);
	}

	for (WaterTile water: scene.waterTiles) {
		glBindVertexArray(water.mesh.vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		scene.shaders[WATER_SHADER].setMat4("model", Helper::createTransformationMatrix(glm::vec3(water.getX(), water.getHeight(), water.getY()), glm::vec3(0), glm::vec3(1.0f)));
		glDrawElements(GL_TRIANGLES, (GLsizei)water.mesh.indices.size(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
	}
	glDisable(GL_BLEND);
	glUseProgram(0);
}
