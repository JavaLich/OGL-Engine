#include "WaterTile.h"






WaterTile::WaterTile(int gridX, int gridY)
{
	x = gridX * SIZE;
	y = gridY * SIZE;
	mesh = generatePlane();
}

WaterTile::~WaterTile()
{
}

float WaterTile::getX()
{
	return x;
}

float WaterTile::getY()
{
	return y;
}

float WaterTile::getHeight()
{
	return height;
}

Mesh WaterTile::generatePlane()
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
			vector.y = 0;
			vertex.position = vector;
			vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);
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
	std::vector<Texture> textures;
	return Mesh(vertices, indices, textures);
}
