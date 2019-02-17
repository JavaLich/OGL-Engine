#include "Player.h"



Player::Player(View *v) : Entity::Entity(0)
{
	position = glm::vec3(0.0f, 300.0f, 0.0f);
	physics = new PhysicsComponent(position, velocity, glm::vec3(1, 25, 1));
	input = new InputComponent();
	view = v;
	speed = 2.0f;
}

	
Player::~Player()
{
}

void Player::update(double delta, GLFWwindow *window,Level* level)
{
	input->update(*this, window, delta);

	physics->position.x += velocity.x;
	physics->position.y += velocity.y;
	physics->position.z += velocity.z;

	if (physics->intersects(level->entities_map[CUBE][0]->physics->position, level->entities_map[CUBE][0]->physics->length)) {
		physics->position.y = level->entities_map[CUBE][0]->physics->position.y + level->entities_map[CUBE][0]->physics->length.y/2 + physics->length.y/2;
		velocity.y = 0;
		if (wantsToJump)
			velocity.y = 5.0f;
	}
	
	position = physics->position;
	transform = Helper::createTransformationMatrix(view->getPosition(), glm::vec3(0), glm::vec3(1.0f));
	view->setPosition(position);
	//Helper::printVec3(position);
}

