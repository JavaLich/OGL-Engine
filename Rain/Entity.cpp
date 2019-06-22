#include "Entity.h"
#include "Level.h"
#include "PhysicsComponent.h"



Entity::Entity(int meshID, PhysicsComponent *physicsComponent)
{
	this->meshID = meshID;
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(physicsComponent->volume / models[meshID].length);
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
	//Perform transformations here on position, rotation, and scale. Make sure to multiply by delta

	setTransform(position, rotation, scale);
}

void Entity::setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	transform = Helper::createTransformationMatrix(pos, rot, scale);
	position = pos;
}
