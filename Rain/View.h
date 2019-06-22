#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx\hash.hpp>
#include <gtc/matrix_transform.hpp>

#include "Helper.h"

static const float near = 0.1f;
static const float far = 1000.0f;

class View
{
public:
	View();
	~View();
	glm::mat4 getProjection();
	glm::mat4 getViewMatrix();
	glm::vec3 getDirection();
	void invertPitch();
	void resetViewMatrix();
	glm::vec3 getPosition();
	void translatePosition(glm::vec3 translation);
	void update(double delta, GLFWwindow* window);
	void setPosition(glm::vec3 position);
	
private:
	glm::vec3 position = glm::vec3(2.0f, 2.0f, 2.0f);
	glm::vec3 direction = glm::vec3(-2.0f, -2.0f, -2.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(0.0f);
	float horizontalAngle = 3.14f;
	float verticalAngle = -3.14f;
	float initialFoV = 45.0f;
	float speed = .6f;
	float mouseSpeed = 0.005f;
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
};

