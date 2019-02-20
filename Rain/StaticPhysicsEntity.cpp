#include "StaticPhysicsEntity.h"
#include "PhysicsComponent.h"


StaticPhysicsEntity::StaticPhysicsEntity(int meshID, glm::vec3 p, glm::vec3 l) : Entity(meshID, new PhysicsComponent(l/models[meshID].length))
{
	position = p;
	ticks = false;
	transform = Helper::createTransformationMatrix(position, glm::vec3(0.0f), l/models[meshID].length);
	gravity = true;
}

void StaticPhysicsEntity::update(Level *level, double delta) {
	physics_->update(*this, *level, delta);
}

void StaticPhysicsEntity::setTransform(glm::vec3 p, glm::vec3 r, glm::vec3 s)
{
	
	Entity::setTransform(p, r, s);
	position = p;
}

StaticPhysicsEntity::~StaticPhysicsEntity()
{
}
