#pragma once
#include "Mesh.h"
#include "SimplexNoise.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <random>
class Terrain
{
public:
	Terrain(int gridX, int gridY, Texture texture, int seed, Texture dirt);
	float getX();
	float getY();

	double getHeightByUnit(int x, int z);
	Mesh mesh;
	~Terrain();
	
private:
	static const float SIZE;
	static const int VERTEX_COUNT=128;
	const float AMPLITUDE = 200.0f;
	const float FREQUENCY = 2.0f;
	const int OCTAVES = 3;
	const float ROUGHNESS = 0.3f;

	float x;
	float y;
	int gridX, gridY;
	SimplexNoise noise;
	Mesh generateTerrain(std::vector<Texture> textures);
	glm::vec3 calculateNormal(int x, int z);
	double getGeneratedHeight(int x, int z);
	
};

