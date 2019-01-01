#pragma once
#include "Mesh.h"
class WaterTile
{
public:
	WaterTile(int gridX, int gridY);
	~WaterTile();

	float getX();
	float getY();
	float getHeight();
	Mesh mesh;
private:
	static const int SIZE = 800;
	static const int VERTEX_COUNT = 4;
	float x, y;
	float height = 0;

	Mesh generatePlane();
};

