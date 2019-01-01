#pragma once
#include "Level.h"
#include <vector>
class World
{
public:
	World();
	~World();
	std::vector<Level> levels;
	int activeLevel = 0;
};

