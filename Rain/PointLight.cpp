#include "PointLight.h"




PointLight::PointLight(glm::vec3 pos)
{
	position = pos;
	ambient = glm::vec3(0.05f);
	diffuse = glm::vec3(1.0f);
	specular = glm::vec3(1.0f);
	constant = 1.0f;
	linear = .00009f;
	quadratic = .0000032f;
}

PointLight::~PointLight()
{
}
