#include "View.h"



View::View()
{
}


View::~View()
{
}

glm::mat4 View::getProjection()
{
	return proj;
}

glm::mat4 View::getViewMatrix()
{
	return view;
}

glm::vec3 View::getDirection()
{
	return direction;
}

void View::invertPitch()
{
	glm::vec3 dir = glm::vec3(
		cos(-verticalAngle) * sin(horizontalAngle),
		sin(-verticalAngle),
		cos(-verticalAngle) * cos(horizontalAngle)
	);
	view = glm::lookAt(position, position + dir, glm::vec3(0.0f, 1.0f, 0.0f));
}

void View::resetViewMatrix()
{
	view = glm::lookAt(position, position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 View::getPosition()
{
	return position;
}

void View::translatePosition(glm::vec3 translation)
{
	position += translation;
}

void View::update(double delta, GLFWwindow * window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);
	horizontalAngle += mouseSpeed * (float)delta * float(width / 2 - xpos);
	verticalAngle += mouseSpeed * (float)delta * -float(height / 2 - ypos);
	if (verticalAngle >= -1.58)verticalAngle = (float)-1.58;
	if (verticalAngle <= -4.7)verticalAngle = (float)-4.7;
	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	view = glm::lookAt(position, position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
	proj = glm::perspective(glm::radians(45.0f), width / (float)height, near, far);
}

void View::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 View::getRightVector()
{
	return glm::normalize(glm::cross(up, direction));
}

glm::vec3 View::getUpVector() {
	return glm::normalize(glm::cross(direction, getRightVector()));
}
