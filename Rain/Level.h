#pragma once
#include "glm.hpp"
#include "Enemy.h"
#include "Scene.h"
#include "StaticPhysicsEntity.h"
#include <vector>
#include "Celestial.h"

struct DirLight {
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
class PointLight;
class Entity;
class Level
{
public:
	Level();
	~Level();
	void processEntity(Entity* entity);
	void updateEntities(double delta);
	void clearEntities();
	std::vector<PointLight> pLights;
	DirLight dirLight;
	std::map<int, std::vector<Entity*>> entities_map;
	std::vector<Entity*> collisionBodies;
	std::vector<Celestial> celestials;
};

