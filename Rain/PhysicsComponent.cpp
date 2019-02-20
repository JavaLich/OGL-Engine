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
	if (entity.gravity&&entity.velocity.y>-25)entity.velocity.y -= .1 * entity.speed * (float)delta;
	physics->position.x += entity.velocity.x;
	physics->position.y += entity.velocity.y;
	physics->position.z += entity.velocity.z;

	if (entity.gravity&&physics->intersects(level.entities_map[CUBE][0]->position, level.entities_map[CUBE][0]->physics_->volume)) {
		physics->position.y = level.entities_map[CUBE][0]->position.y + level.entities_map[CUBE][0]->physics_->volume.y / 2 + physics->length.y / 2;
		entity.velocity.y = 0;
	}

	entity.position = physics->position;
}
