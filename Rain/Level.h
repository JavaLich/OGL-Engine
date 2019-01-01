#pragma once
#include "glm.hpp"
#include "Entity.h"
#include "Scene.h"
#include "StaticPhysicsEntity.h"
#include <vector>


struct DirLight {
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class Level
{
public:
	Level();
	~Level();
	void processEntity(Entity* entity);
	void updateEntities(double delta);
	void clearEntities();
	std::map<int, std::vector<Entity*>> entities_map;
	std::vector<PointLight> pLights;
	DirLight dirLight;

};

