#include "Celestial.h"

Celestial::~Celestial()
{
}

void Celestial::setTransform(glm::vec3 pos, glm::vec3 rot)
{
	transform = Helper::createTransformationMatrix(pos, rot, glm::vec3(1.0f));
	position = pos;
}
