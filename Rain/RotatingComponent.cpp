#include "RotatingComponent.h"



RotatingComponent::RotatingComponent(glm::vec3 rot)
{
	rotation = rot;
}

RotatingComponent::RotatingComponent()
{
}


RotatingComponent::~RotatingComponent()
{
}

void RotatingComponent::update(Entity & entity, double delta)
{
	entity.rotation += glm::vec3(rotation.x*delta, rotation.y*delta, rotation.z*delta);
}
