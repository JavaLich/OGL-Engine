#include "LevelRenderer.h"



LevelRenderer::LevelRenderer()
{
}


LevelRenderer::~LevelRenderer()
{
}

void LevelRenderer::render(Scene & scene, World world)
{
	scene.shaders.at(SHADER).bind();
	scene.shaders.at(SHADER).setMat4("view", scene.view.getViewMatrix());
	scene.shaders.at(SHADER).setMat4("proj", scene.view.getProjection());
	scene.shaders.at(SHADER).setVec3("cameraPos", scene.view.getPosition());

	//Directional Light
	scene.shaders.at(SHADER).setVec3("dirLight.direction", world.levels[world.activeLevel].dirLight.direction);
	scene.shaders.at(SHADER).setVec3("dirLight.ambient", world.levels[world.activeLevel].dirLight.ambient);
	scene.shaders.at(SHADER).setVec3("dirLight.diffuse", world.levels[world.activeLevel].dirLight.diffuse);
	scene.shaders.at(SHADER).setVec3("dirLight.specular", world.levels[world.activeLevel].dirLight.specular);
	scene.shaders.at(SHADER).setVec4("plane", scene.clipPlane);

	//Point lights
	int lights = world.levels[world.activeLevel].pLights.size();

	for (int i = 0; i < lights; i++) {
		scene.loadPointLight(world.levels[world.activeLevel].pLights.at(i), i);
	}

	for (std::map<int, std::vector<Entity*>>::iterator it = world.levels[world.activeLevel].entities_map.begin(); it != world.levels[world.activeLevel].entities_map.end(); ++it) {
		for (Mesh mesh : models[it->first].meshes) {
			mesh.setupRender(scene.shaders[SHADER]);
			scene.shaders.at(SHADER).setFloat("material.shininess", 64);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			for (Entity* entity : it->second) {
				scene.shaders[SHADER].setMat4("model", Helper::createTransformationMatrix(entity->transform, glm::vec3(0.0f), glm::vec3(glm::radians(-90.0f), 0.0f, glm::radians(-90.0f)), glm::vec3(10.0f)));
				glDrawElements(GL_TRIANGLES, (GLsizei)mesh.indices.size(), GL_UNSIGNED_INT, 0);
			}
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glBindVertexArray(0);
		}
	}

	glUseProgram(0);
}
