#include "Level.h"



Level::Level()
{
	
	StaticPhysicsEntity* room = new StaticPhysicsEntity(CUBE, glm::vec3(0.0f), glm::vec3(1000.0f, 10.0f, 1000.0f));
	//Entity* suit = new Entity(2);
	pLights.push_back(glm::vec3(0.7f, 10.0f, 2.0f));
	pLights.at(0).ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	pLights.at(0).diffuse = glm::vec3(.8f, .8f, .8f);
	pLights.at(0).specular = glm::vec3(1.0f, 1.0f, 1.0f);
	pLights[0].position.y = 50.0f;
	StaticPhysicsEntity* tree = new StaticPhysicsEntity(BIRCH_TREE, pLights[0].position, glm::vec3(10, 10, 20));
	tree->ticks = false;
	room->ticks = false;
	//suit->ticks = false;
	
	//tree->setTransform(pLights[0].position, glm::vec3(0), glm::vec3(1.0f));
	//suit->setTransform(glm::vec3(0, 5, 0), glm::vec3(0), glm::vec3(1.0f));
	processEntity(room);
	processEntity(tree);
	//processEntity(suit);
	dirLight.ambient = glm::vec3(.2f, .2f, .2f);
	dirLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	dirLight.diffuse = glm::vec3(0.3f);
	dirLight.specular = glm::vec3(0.3f);
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
			if (it->second.at(i)->ticks) it->second.at(i)->update(delta);
		}
	}

	
	
}

void Level::clearEntities()
{
	entities_map.clear();
}
