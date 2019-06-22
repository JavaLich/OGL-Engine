#include "PhysicsComponent.h"



PhysicsComponent::PhysicsComponent()
{
	physics = new Physics();
	volume = glm::vec3(0.0f);
}

PhysicsComponent::PhysicsComponent(glm::vec3 l)
{
	physics = new Physics();
	volume = l;
}


PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::update(Entity & entity,Level &level, double delta)
{
	physics->position = entity.position;
	physics->velocity = entity.velocity;
	physics->length = volume;
	physics->position.x += entity.velocity.x;
	physics->position.y += entity.velocity.y;
	physics->position.z += entity.velocity.z;

	entity.position = physics->position;
}
