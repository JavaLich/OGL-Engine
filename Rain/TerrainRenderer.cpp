#include "TerrainRenderer.h"



TerrainRenderer::TerrainRenderer()
{
}


TerrainRenderer::~TerrainRenderer()
{
}

void TerrainRenderer::render(Scene & scene, World world)
{
	scene.shaders.at(TERRAIN_SHADER).bind();
	scene.shaders.at(TERRAIN_SHADER).setMat4("view", scene.view.getViewMatrix());
	scene.shaders.at(TERRAIN_SHADER).setMat4("proj", scene.view.getProjection());
	scene.shaders.at(TERRAIN_SHADER).setVec3("cameraPos", scene.view.getPosition());

	//Directional Light
	scene.shaders.at(TERRAIN_SHADER).setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	scene.shaders.at(TERRAIN_SHADER).setVec3("dirLight.ambient", glm::vec3(.75f));
	scene.shaders.at(TERRAIN_SHADER).setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	scene.shaders.at(TERRAIN_SHADER).setVec3("dirLight.specular", glm::vec3(0.0f));

	scene.shaders.at(TERRAIN_SHADER).setVec4("plane", scene.clipPlane);

	//Point lights
	int lights = NR_POINT_LIGHTS;
	//TODO Swith to pLights.size()
	for (int i = 0; i < lights; i++) {
		scene.loadPointLight(scene.pLights.at(i), i);
	}
	scene.shaders[TERRAIN_SHADER].setInt("material.texture_diffuse1", 0);
	scene.shaders[TERRAIN_SHADER].setInt("material.texture_diffuse2", 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, scene.terrains[0].mesh.textures[0].id);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, scene.terrains[0].mesh.textures[1].id);

	for (Terrain terrain : scene.terrains) {
		glBindVertexArray(terrain.mesh.vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		scene.shaders[TERRAIN_SHADER].setMat4("model", Helper::createTransformationMatrix(glm::vec3(terrain.getX(), 0, terrain.getY()), glm::vec3(0), glm::vec3(1.0f)));
		glDrawElements(GL_TRIANGLES, (GLsizei)terrain.mesh.indices.size(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
	}
	glUseProgram(0);
}
