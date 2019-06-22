#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx\hash.hpp>

#include "Shader.h"
#include "PointLight.h"
#include "Model.h"
#include "Mesh.h"
#include "Terrain.h"
#include "WaterTile.h"
#include "WaterFrameBuffers.h"
#include "View.h"
#include "Helper.h"
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include "Entity.h"

#define NR_POINT_LIGHTS 4;
struct Camera {
	glm::vec3 position = glm::vec3(2.0f, 2.0f, 2.0f);
	glm::vec3 direction = glm::vec3(-2.0f, -2.0f, -2.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(0.0f);
	
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float initialFoV = 45.0f;
	float speed = 1.0f;
	float mouseSpeed = 0.005f;
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
};

//ID for mesh
static const uint32_t BIRCH_TREE = 0;
static const uint32_t CUBE = 1;

//ID for shader
static const uint16_t SHADER = 0;
static const uint16_t TERRAIN_SHADER = 3;
static const uint16_t WATER_SHADER = 2;
static const uint16_t STAR_SHADER = 1;

//ID for texture
static const uint32_t CHECKER = 0;
static const uint32_t WHITE = 1;

extern std::vector<Model> models;
extern std::vector<GLuint> texs;

class Level;
class Entity;
class Scene
{
public:
	Scene();
	~Scene();
	void init();
	void processEntity(Entity* entity);
	void processTerrain(Terrain terrain);
	void processWaterTile(WaterTile waterTile);
	void updateEntities(Level*level, double delta);
	void clearEntities();
	void updateCamera(double delta, GLFWwindow* window);
	void loadPointLight(PointLight pLight, uint16_t index);
	GLuint getTextureFromFile(const char * path, const std::string & directory, bool gamma = false);
	
	
	std::vector<Shader> shaders;
	std::vector<PointLight> pLights;
	std::vector<Terrain> terrains;
	std::vector<WaterTile> waterTiles;
	std::map<int, std::vector<Entity*>> entities_map;
	//std::vector<Celestial> celestials;
	Camera camera;
	glm::vec4 clipPlane;
	WaterFrameBuffers fbos;
	View view;
	float counter = 0.0f;
};

