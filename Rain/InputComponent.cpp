#include "InputComponent.h"



InputComponent::InputComponent()
{
	
}


InputComponent::~InputComponent()
{
}

void InputComponent::update(Player &entity, GLFWwindow* window, double delta)
{
	entity.velocity.x = 0;
	entity.velocity.z = 0;
	entity.wantsToJump = false;
	glm::vec3 lookDirection = glm::vec3(entity.view->getDirection().x, 0.0f, entity.view->getDirection().z);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		entity.velocity += entity.speed * glm::normalize(lookDirection) *(float)delta;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		entity.velocity -= entity.speed * glm::normalize(lookDirection)*(float)delta;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		entity.velocity -= glm::normalize(glm::cross(entity.view->getDirection(), glm::vec3(0.0f, 1.0f, 0.0f))) * entity.speed*(float)delta;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		entity.velocity += glm::normalize(glm::cross(entity.view->getDirection(), glm::vec3(0.0f, 1.0f, 0.0f))) * entity.speed*(float)delta;
	/*if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	physics->position.y -= speed*delta;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	physics->position.y += speed*delta;*/
	
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)entity.wantsToJump = true;
}
