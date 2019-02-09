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
	
	
}

void Entity::setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	transform = Helper::createTransformationMatrix(pos, rot, scale);
}
