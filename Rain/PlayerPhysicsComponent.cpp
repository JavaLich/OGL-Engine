#include "PlayerPhysicsComponent.h"



PlayerPhysicsComponent::PlayerPhysicsComponent()
{
}


PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}

void PlayerPhysicsComponent::update(Entity & entity, Level * level, double delta)
{
	Player &player =(Player&) entity;
	if (entity.velocity.y>-50)entity.velocity.y -= .1 * entity.speed * (float)delta;
	entity.physics->position.x += entity.velocity.x;
	entity.physics->position.y += entity.velocity.y;
	entity.physics->position.z += entity.velocity.z;

	if (entity.physics->intersects(level->entities_map[CUBE][0]->physics->position, level->entities_map[CUBE][0]->physics->length)) {
		entity.physics->position.y = level->entities_map[CUBE][0]->physics->position.y + level->entities_map[CUBE][0]->physics->length.y / 2 + entity.physics->length.y / 2;
		entity.velocity.y = 0;
		if (player.wantsToJump)
			entity.velocity.y = 5.0f;
	}

	entity.position = entity.physics->position;
}
