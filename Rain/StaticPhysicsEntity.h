#pragma once
#include "Entity.h"
#include "Scene.h"
class PhysicsComponent;
class StaticPhysicsEntity :
	public Entity
{
public:
	StaticPhysicsEntity(int meshID, glm::vec3 p, glm::vec3 l);
	~StaticPhysicsEntity();
	glm::vec3 position;
	virtual void update(Level *level, double delta);
	void setTransform(glm::vec3 p, glm::vec3 r, glm::vec3 s);
};

