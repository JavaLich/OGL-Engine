#include "Celestial.h"

Celestial::~Celestial()
{
}

void Celestial::setTransform(glm::vec3 pos, glm::vec3 rot)
{
	transform = Helper::createTransformationMatrix(pos, rot, glm::vec3(1.0f));
	position = pos;
}

glm::vec3 Celestial::getTempColorShift()
{
	return  glm::vec3(temperature * (0.0534 / 255.0) - (43.0 / 255.0),
		temperature * (0.0628 / 255.0) - (77.0 / 255.0),
		temperature * (0.0735 / 255.0) - (115.0 / 255.0));
}
