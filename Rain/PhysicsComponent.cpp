#include "PhysicsComponent.h"



PhysicsComponent::PhysicsComponent(glm::vec3 & p, glm::vec3 & v, glm::vec3 l)
{
	position = p;
	velocity = v;
	length = l;
}

PhysicsComponent::PhysicsComponent()
{
	position = glm::vec3(0.0f);
	velocity = glm::vec3(0.0f);
	length = glm::vec3(0.0f);
}

PhysicsComponent::~PhysicsComponent()
{
}

bool PhysicsComponent::intersects(glm::vec3 p, glm::vec3 l)
{
	float aminX = position.x - (length.x / 2);
	float amaxX = position.x + (length.x / 2);
	float aminY = position.y - (length.y / 2);
	float amaxY = position.y + (length.y / 2);
	float aminZ = position.z - (length.z / 2);
	float amaxZ = position.z + (length.z / 2);

	float bminX = p.x - (l.x / 2);
	float bmaxX = p.x + (l.x / 2);
	float bminY = p.y - (l.y / 2);
	float bmaxY = p.y + (l.y / 2);
	float bminZ = p.z - (l.z / 2);
	float bmaxZ = p.z + (l.z / 2);

	return (aminX <= bmaxX && amaxX>= bminX) &&
		(aminY <= bmaxY && amaxY >= bminY) &&
		(aminZ <= bmaxZ && amaxZ >= bminZ);
}
