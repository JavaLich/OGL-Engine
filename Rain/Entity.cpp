#include "Entity.h"
#include "Level.h"
#include "PhysicsComponent.h"



Entity::Entity(int meshID, PhysicsComponent *physicsComponent)
{
	this->meshID = meshID;
	position = glm::vec3(0.0f);
	transform = Helper::createTransformationMatrix(position, glm::vec3(0.0f), physicsComponent->volume / models[meshID].length);
	velocity = glm::vec3(0.0f);
	physics_ = physicsComponent;
}


Entity::~Entity()
{
}
void Entity::update(Level &level, double delta)
{
	physics_->update(*this, level, delta);
	setTransform(position, glm::vec3(0.0f), physics_->volume / models[meshID].length);
}
void Entity::setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	transform = Helper::createTransformationMatrix(pos, rot, scale);
	position = pos;
}
