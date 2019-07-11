#include "StarRenderer.h"



StarRenderer::StarRenderer()
{
}


StarRenderer::~StarRenderer()
{
}

float timeF = 0.0f;

void StarRenderer::render(Scene & scene, World & world)
{
	timeF += 0.0003f;
	scene.shaders.at(STAR_SHADER).bind();
	scene.shaders.at(STAR_SHADER).setMat4("view", scene.view.getViewMatrix());
	scene.shaders.at(STAR_SHADER).setMat4("proj", scene.view.getProjection());
	scene.shaders.at(STAR_SHADER).setVec3("cameraPos", scene.view.getPosition());

	//Directional Light
	scene.shaders.at(STAR_SHADER).setVec3("dirLight.direction", world.levels[world.activeLevel].dirLight.direction);
	scene.shaders.at(STAR_SHADER).setVec3("dirLight.ambient", world.levels[world.activeLevel].dirLight.ambient);
	scene.shaders.at(STAR_SHADER).setVec3("dirLight.diffuse", world.levels[world.activeLevel].dirLight.diffuse);
	scene.shaders.at(STAR_SHADER).setVec3("dirLight.specular", world.levels[world.activeLevel].dirLight.specular);

	scene.shaders.at(STAR_SHADER).setVec4("plane", scene.clipPlane);

	//Point lights
	int lights = world.levels[world.activeLevel].pLights.size();

	for (int i = 0; i < lights; i++) {
		scene.loadPointLight(world.levels[world.activeLevel].pLights.at(i), i);
	}

	scene.shaders[STAR_SHADER].setFloat("time", timeF);

	for (Mesh mesh : models[1].meshes) {
		scene.shaders.at(STAR_SHADER).setFloat("material.shininess", 32);
		glActiveTexture(GL_TEXTURE0);
		scene.shaders[SHADER].setInt("starSpectrum", 0);
		glBindTexture(GL_TEXTURE_2D, texs.at(1));
		glBindVertexArray(mesh.vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		for (Celestial c : world.levels[world.activeLevel].celestials) {
			scene.shaders[STAR_SHADER].setMat4("model", c.transform);
			scene.shaders[STAR_SHADER].setVec3("center", c.position);
			scene.shaders[STAR_SHADER].setFloat("radius", c.radius);
			scene.shaders[STAR_SHADER].setFloat("realRadius", c.realRadius);
			scene.shaders[STAR_SHADER].setFloat("temperature", c.temperature);
			scene.shaders[STAR_SHADER].setVec3("colorShift", c.getTempColorShift());
			glDrawElements(GL_PATCHES, (GLsizei)mesh.indices.size(), GL_UNSIGNED_INT, 0);
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
	}

	glUseProgram(0);

	scene.shaders[CORONA_SHADER].bind();
	scene.shaders.at(CORONA_SHADER).setMat4("view", scene.view.getViewMatrix());
	scene.shaders.at(CORONA_SHADER).setMat4("proj", scene.view.getProjection());
	scene.shaders[CORONA_SHADER].setVec3("cameraPos", scene.view.getPosition());
	scene.shaders[CORONA_SHADER].setFloat("time", timeF);
	for (Mesh mesh : models[PLANE].meshes) {
		glActiveTexture(GL_TEXTURE0);
		scene.shaders[CORONA_SHADER].setInt("material.texture_diffuse1", 0);
		glBindTexture(GL_TEXTURE_2D, texs.at(0));
		glActiveTexture(GL_TEXTURE1);
		scene.shaders[CORONA_SHADER].setInt("starSpectrum", 1);
		glBindTexture(GL_TEXTURE_2D, texs.at(1));
		glBindVertexArray(mesh.vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		for (Celestial c : world.levels[world.activeLevel].celestials) {
			scene.shaders[CORONA_SHADER].setVec3("centerPos", c.position);
			scene.shaders[CORONA_SHADER].setFloat("size", c.radius*4);
			scene.shaders[CORONA_SHADER].setMat4("model", c.transform);
			glDrawElements(GL_TRIANGLES, (GLsizei)mesh.indices.size(), GL_UNSIGNED_INT, 0);
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
	}
	glUseProgram(0);
}
