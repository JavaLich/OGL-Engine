#include "Player.h"



Player::Player(View *v) : Entity::Entity(0, new PlayerPhysicsComponent(glm::vec3(1, 25, 1)))
{
	position = glm::vec3(0.0f, 0.0f, -200.0f);
	input = new InputComponent();
	physics_ = new PlayerPhysicsComponent(glm::vec3(1, 50, 1));
	view = v;
}

	
Player::~Player()
{
}

void Player::update(double delta, GLFWwindow *window,Level* level)
{
	input->update(*this, window, delta);
	physics_->update(*this, *level, delta);
	
	transform = Helper::createTransformationMatrix(position, glm::vec3(0), glm::vec3(1.0f));
//	Helper::printVec3(position);
}

