#include "Scene.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::vector<Model> models = std::vector<Model>();
std::vector<GLuint> texs = std::vector<GLuint>();

Scene::Scene()
{
	clipPlane = glm::vec4(0.0f);
}


Scene::~Scene()
{
}

void Scene::init()
{
	Shader shader = Shader("assets/shaders/shader.vert", "assets/shaders/shader.frag", "assets/shaders/shader.cs", "assets/shaders/shader.es");
	Shader sphereShader = Shader("assets/shaders/sphereShader.vert", "assets/shaders/sphereShader.frag", "assets/shaders/sphereShader.cs", "assets/shaders/sphereShader.es");
	/*Shader terrainShader = Shader("assets/shaders/terrainShader.vert", "assets/shaders/terrainShader.frag");
	Shader waterShader = Shader("assets/shaders/waterShader.vert", "assets/shaders/waterShader.frag");*/
	shaders.push_back(shader);
	shaders.push_back(sphereShader);
	shaders.push_back(Shader("assets/shaders/corona.vert", "assets/shaders/corona.frag"));
	/*shaders.push_back(terrainShader);
	shaders.push_back(waterShader);*/
	
	pLights.push_back(glm::vec3(0.7f, 0.2f, 2.0f));
	pLights.at(0).ambient = glm::vec3(0.05f, 0, 0);
	pLights.at(0).diffuse = glm::vec3(.8f, 0, 0);
	pLights.at(0).specular = glm::vec3(1.0f, 0, 0);
	pLights.push_back(glm::vec3(2.3f, 5.0f, -4.0f));
	pLights.push_back(glm::vec3(-4.0f, 2.0f, -12.0f));
	pLights.push_back(glm::vec3(0.0f, 0.0f, -3.0f));
	
	Model birchTree = Model("assets/models/enemy/enemy.dae");
	Model room =  Model("assets/models/crate/Crate1.dae");
	Model sphere =  Model("assets/models/sphere.obj");
	Model plane =  Model("assets/models/plane.obj");
	models.push_back(birchTree);// MESH ID : 0
	models.push_back(room);
	models.push_back(sphere);
	models.push_back(plane);
	texs.push_back(getTextureFromFile("white.png", "assets/textures"));
	texs.push_back(getTextureFromFile("star_spectrum.png", "assets/textures"));
}

void Scene::processEntity(Entity* entity)
{
	if (entities_map.find(entity->meshID) == entities_map.end()) {
		std::vector<Entity*> batch = std::vector<Entity*>();
		batch.push_back(entity);
		entities_map.insert(std::pair < int, std::vector<Entity*>>(entity->meshID, batch) );
	}
	else {
		entities_map.at(entity->meshID).push_back(entity);
	}
	
}

void Scene::processTerrain(Terrain terrain)
{
	terrains.push_back(terrain);
}

void Scene::processWaterTile(WaterTile waterTile)
{
	waterTiles.push_back(waterTile);
}

void Scene::updateEntities(Level* level, double delta)
{
	for (std::map<int, std::vector<Entity*>>::iterator it = entities_map.begin(); it != entities_map.end(); ++it) {
		for (int i = 0; i < it->second.size(); i++) {
			if(it->second.at(i)->ticks) it->second.at(i)->update(*level, delta);
		}
	}
}

void Scene::clearEntities()
{
	entities_map.clear();
}

void Scene::updateCamera(double delta, GLFWwindow* window)
{
	counter += 0.0005f*delta;
	view.update(delta, window);
}

void Scene::loadPointLight(PointLight pLight, uint16_t index)
{
	shaders.at(SHADER).setVec3(("pointLights[" + std::to_string(index) + "].position").c_str(), pLight.position);
	shaders.at(SHADER).setVec3(("pointLights[" + std::to_string(index) + "].ambient").c_str(), pLight.ambient);
	shaders.at(SHADER).setVec3(("pointLights[" + std::to_string(index) + "].diffuse").c_str(), pLight.diffuse);
	shaders.at(SHADER).setVec3(("pointLights[" + std::to_string(index) + "].specular").c_str(), pLight.specular);
	shaders.at(SHADER).setFloat(("pointLights[" + std::to_string(index) + "].constant").c_str(), pLight.constant);
	shaders.at(SHADER).setFloat(("pointLights[" + std::to_string(index) + "].linear").c_str(), pLight.linear);
	shaders.at(SHADER).setFloat(("pointLights[" + std::to_string(index) + "].quadratic").c_str(), pLight.quadratic);
}

GLuint Scene::getTextureFromFile(const char * path, const std::string & directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

