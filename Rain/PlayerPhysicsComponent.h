#pragma once
#include "PhysicsComponent.h"
#include "Player.h"
class Player;
class PlayerPhysicsComponent :
	public PhysicsComponent
{
public:
	PlayerPhysicsComponent();
	PlayerPhysicsComponent(glm::vec3 l) : PhysicsComponent(l) {

	}
	~PlayerPhysicsComponent();
	void update(Entity &entity, Level& level, double delta) override;
};

