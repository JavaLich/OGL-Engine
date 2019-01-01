#include "Terrain.h"

const float Terrain::SIZE = 800;


Terrain::Terrain(int gridX, int gridY, Texture texture, int seed, Texture dirt)
{
	noise = SimplexNoise(seed);
	this->gridX = gridX;
	this->gridY = gridY;
	std::vector<Texture> texs;
	texs.push_back(texture);
	texs.push_back(dirt);
	mesh = generateTerrain(texs);
	x = gridX * SIZE;
	y = gridY * SIZE;
}

float Terrain::getX()
{
	return x;
}

float Terrain::getY()
{
	return y;
}


Terrain::~Terrain()
{
}

Mesh Terrain::generateTerrain(std::vector<Texture> textures)
{
	int count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			Vertex vertex;
			glm::vec3 vector;
			vector.x = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			vector.z = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			vector.y = (float)getGeneratedHeight(j, i);
			vertex.position = vector;
			vector = calculateNormal(j, i);
			vertex.normal = vector;
			glm::vec2 tC;
			tC.x = (float)j / ((float)VERTEX_COUNT - 1);
			tC.y = (float)i / ((float)VERTEX_COUNT - 1);
			vertex.texCoord = tC;
			vertices.push_back(vertex);
			
		}
		
	}
	
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices.push_back(topLeft);
			indices.push_back(bottomLeft);
			indices.push_back(topRight);
			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
		}
	}
	return Mesh(vertices, indices, textures);
}

glm::vec3 Terrain::calculateNormal(int x, int z)
{
	double heightL = getGeneratedHeight(x - 1, z);
	double heightR = getGeneratedHeight(x + 1, z);
	double heightD = getGeneratedHeight(x, z - 1);
	double heightU = getGeneratedHeight(x, z + 1);
	glm::vec3 normal = glm::vec3(heightL - heightR, 2.0f, heightD - heightU);
	normal = glm::normalize(normal);
	return normal;
}

double Terrain::getGeneratedHeight(int x, int z)
{
	float total = 0.0f;
	float amplitude = AMPLITUDE;
	float freq = (float) pow(2, OCTAVES) * FREQUENCY;
	for (int i = 0; i < OCTAVES; i++) {
		freq /= 2;
		amplitude *= ROUGHNESS;
		total += (float)noise.getInterpolatedNoise((x + (gridX*(VERTEX_COUNT - 1))) / freq, (z + (gridY*(VERTEX_COUNT - 1))) / freq)*amplitude;
	}

	return total;
}

double Terrain::getHeightByUnit(int x, int z)
{
	int vertX = (VERTEX_COUNT*x) / SIZE;
	int vertZ = (VERTEX_COUNT*z) / SIZE;
	return getGeneratedHeight(vertX, vertZ);
}
