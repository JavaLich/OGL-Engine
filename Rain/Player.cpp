#include "Player.h"



Player::Player(View *v) : Entity::Entity(0)
{
	position = glm::vec3(0.0f, 300.0f, 0.0f);
	physics = new PhysicsComponent(position, velocity, glm::vec3(1, 25, 1));
	view = v;
	speed = 2.0f;
}


Player::~Player()
{
}

void Player::update(double delta, GLFWwindow *window, Level* level)
{
	glm::vec3 lookDirection = glm::vec3(view->getDirection().x, 0.0f, view->getDirection().z);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		velocity += speed * glm::normalize(lookDirection) *(float)delta;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		velocity -= speed * glm::normalize(lookDirection)*(float)delta;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		velocity -= glm::normalize(glm::cross(view->getDirection(), glm::vec3(0.0f, 1.0f, 0.0f))) * speed*(float)delta;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		velocity += glm::normalize(glm::cross(view->getDirection(), glm::vec3(0.0f, 1.0f, 0.0f))) * speed*(float)delta;
	/*if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		physics->position.y -= speed*delta;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		physics->position.y += speed*delta;*/
	if (velocity.y>-50)velocity.y -= .1 * speed * (float) delta;


	physics->position.x += velocity.x;
	physics->position.y += velocity.y;
	physics->position.z += velocity.z;
	velocity.x = 0;
	velocity.z = 0;

	if (physics->intersects(level->entities_map[CUBE][0]->physics->position, level->entities_map[CUBE][0]->physics->length)) {
		physics->position.y = level->entities_map[CUBE][0]->physics->position.y + level->entities_map[CUBE][0]->physics->length.y/2 + physics->length.y/2;
		velocity.y = 0;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			velocity.y = 5.0f;
	}
	
	position = physics->position;
	transform = Helper::createTransformationMatrix(view->getPosition(), glm::vec3(0), glm::vec3(1.0f));
	view->setPosition(position);
}

