#pragma once
#include "Entity.h"
class Enemy :
	public Entity
{
public:
	Enemy(int meshID, PhysicsComponent* physicsComponent) : Entity(meshID, physicsComponent) {
		gravity = true;
		ticks = true;
		rotation = glm::vec3(3.1415 / 2/*90 degrees*/, 3.1415, 0);
		scale = glm::vec3(scale.x, scale.y / 2, scale.z * 2);
	}
	~Enemy();
};

