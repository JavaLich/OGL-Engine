#pragma once
#include "PhysicsComponent.h"
#include "Player.h"
class Player;
class PlayerPhysicsComponent :
	public PhysicsComponent
{
public:
	PlayerPhysicsComponent();
	~PlayerPhysicsComponent();
	virtual void update(Entity &player, Level* level, double delta);
};

