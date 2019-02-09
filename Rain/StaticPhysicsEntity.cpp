#include "StaticPhysicsEntity.h"



StaticPhysicsEntity::StaticPhysicsEntity(int meshID, glm::vec3 p, glm::vec3 l) : Entity(meshID)
{
	position = p;
	ticks = false;
	transform = Helper::createTransformationMatrix(position, glm::vec3(0.0f), l/models[meshID].length);
	physics = new PhysicsComponent(position, glm::vec3(0.0f), l);
}

void StaticPhysicsEntity::update(double delta) {
}

void StaticPhysicsEntity::setTransform(glm::vec3 p, glm::vec3 r, glm::vec3 s)
{
	Entity::setTransform(p, r, s);
	position = p;
}

StaticPhysicsEntity::~StaticPhysicsEntity()
{
}
