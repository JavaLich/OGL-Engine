#include "Level.h"
#include "PhysicsComponent.h"


Level::Level()
{
	
	/*Entity* room = new Entity(CUBE, new PhysicsComponent(glm::vec3(1000.0f, 10.0f, 1000.0f)));
	room->position.y = -100.0f;
	room->gravity = false;
	//Entity* suit = new Entity(2);
	
	Enemy* tree = new Enemy(BIRCH_TREE, new PhysicsComponent(glm::vec3(10, 20, 10)));	
	collisionBodies.push_back(room);
	collisionBodies.push_back(tree);
	tree->position= pLights[0].position;
	room->ticks = true;
	//suit->ticks = false;
	
	//tree->setTransform(pLights[0].position, glm::vec3(0), glm::vec3(1.0f));
	//suit->setTransform(glm::vec3(0, 5, 0), glm::vec3(0), glm::vec3(1.0f));
	processEntity(room);
	processEntity(tree);*/
	//processEntity(suit
	pLights.push_back(glm::vec3(0.7f, 120.0f, -50.0f));
	pLights.at(0).ambient = glm::vec3(0.0f);
	pLights.at(0).diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
	pLights.at(0).specular = glm::vec3(0.0f);
	Entity* sphere = new Entity(1, new PhysicsComponent(glm::vec3(100.0, 100.0f, 100.0f)));
	collisionBodies.push_back(sphere);
	processEntity(sphere);
	dirLight.ambient = glm::vec3(0.2f);
	dirLight.direction = glm::vec3(0.2f, -1.0f, 0.3f);
	dirLight.diffuse = glm::vec3(0.8f);
	dirLight.specular = glm::vec3(1.0f);
	celestials.push_back(Celestial(10.0f));

}


Level::~Level()
{
}



void Level::processEntity(Entity * entity)
{
	if (entities_map.find(entity->meshID) == entities_map.end()) {
		std::vector<Entity*> batch = std::vector<Entity*>();
		batch.push_back(entity);
		entities_map.insert(std::pair < int, std::vector<Entity*>>(entity->meshID, batch));
	}
	else {
		entities_map.at(entity->meshID).push_back(entity);
	}
}

void Level::updateEntities(double delta)
{
	for (std::map<int, std::vector<Entity*>>::iterator it = entities_map.begin(); it != entities_map.end(); ++it) {
		for (int i = 0; i < it->second.size(); i++) {
			if (it->second.at(i)->ticks) it->second.at(i)->update(*this, delta);
		}
	}

	
	
}

void Level::clearEntities()
{
	entities_map.clear();
}
