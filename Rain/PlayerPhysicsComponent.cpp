#include "PlayerPhysicsComponent.h"



PlayerPhysicsComponent::PlayerPhysicsComponent()
{
	PhysicsComponent();
}


PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}

void PlayerPhysicsComponent::update(Entity & entity, Level & level, double delta)
{ 
	physics->position = entity.position;
	physics->velocity = entity.velocity;
	physics->length = volume;
	Player &player =(Player&) entity;
	if (entity.velocity.y>-50)entity.velocity.y -= .1 * entity.speed * (float)delta;
	physics->position.x += entity.velocity.x;
	physics->position.y += entity.velocity.y;
	physics->position.z += entity.velocity.z;

	if (physics->intersects(level.entities_map[CUBE][0]->position, level.entities_map[CUBE][0]->physics_->volume)) {
		physics->position.y = level.entities_map[CUBE][0]->position.y + level.entities_map[CUBE][0]->physics_->volume.y / 2 + physics->length.y / 2;
		entity.velocity.y = 0;
		if (player.wantsToJump)
			entity.velocity.y = 5.0f;
	}

	entity.position = physics->position;
}
