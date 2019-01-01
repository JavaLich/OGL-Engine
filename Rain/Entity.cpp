#include "Entity.h"



Entity::Entity(int meshID)
{
	this->meshID = meshID;
	
	transform = glm::mat4(1.0f);
	physics = new PhysicsComponent();
}


Entity::~Entity()
{
}
void Entity::update(double delta)
{
	for (int i = 0; i < components.size(); i++) {
		if (components[i].ticks)components[i].update(delta);
	}
	
}

void Entity::attachComponent(Component comp)
{
	components.push_back(comp);
}

void Entity::setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	transform = Helper::createTransformationMatrix(pos, rot, scale);
}
