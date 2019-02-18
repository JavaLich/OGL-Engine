#include "Player.h"



Player::Player(View *v) : Entity::Entity(0)
{
	position = glm::vec3(0.0f, 300.0f, 0.0f);
	physics = new Physics(position, velocity, glm::vec3(1, 25, 1));
	input = new InputComponent();
	physics_ = new PlayerPhysicsComponent();
	view = v;
}

	
Player::~Player()
{
}

void Player::update(double delta, GLFWwindow *window,Level* level)
{
	input->update(*this, window, delta);
	physics_->update(*this, level, delta);
	transform = Helper::createTransformationMatrix(position, glm::vec3(0), glm::vec3(1.0f));
	view->setPosition(position);
//	Helper::printVec3(position);
}

