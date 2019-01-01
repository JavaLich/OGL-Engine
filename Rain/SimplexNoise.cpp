#include "SimplexNoise.h"



SimplexNoise::SimplexNoise(int numberOfOctaves, double persistence, int seed)
{
	this->persistence = persistence;
	this->numberOfOctaves = numberOfOctaves;
	this->seed = seed;

	for (int i = 0; i < numberOfOctaves; i++) {
		octaves.push_back(NoiseOctave(rand() % INT_MAX));
	}
}

SimplexNoise::SimplexNoise()
{
	this->persistence = 0.5;
	this->numberOfOctaves = 4;
	this->seed = 1000;
	for (int i = 0; i < numberOfOctaves; i++) {
		octaves.push_back(NoiseOctave(rand() % INT_MAX));
	}
}

SimplexNoise::SimplexNoise(int seed)
{
	this->persistence = 0.5;
	this->numberOfOctaves = 4;
	this->seed = seed;
}



SimplexNoise::~SimplexNoise()
{
}

double SimplexNoise::getInterpolatedNoise(float x, float z)
{
	int intX = (int)x;
	int intZ = (int)z;
	float fracX = x - intX;
	float fracZ = z - intZ;

	float v1 = getSmoothNoise(intX, intZ);
	float v2 = getSmoothNoise(intX + 1, intZ);
	float v3 = getSmoothNoise(intX, intZ + 1);
	float v4 = getSmoothNoise(intX + 1, intZ + 1);
	float i1 = Helper::interpolate(v1, v2, fracX);
	float i2 = Helper::interpolate(v3, v4, fracX);

	return Helper::interpolate(i1, i2, fracZ);
}

double SimplexNoise::getSmoothNoise(int x, int y)
{
	double corners = (getNoise(x - 1, y - 1) + getNoise(x + 1, y - 1) + getNoise(x - 1, y + 1) + getNoise(x + 1, y + 1)) / 16.0f;
	double sides = (getNoise(x - 1, y) + getNoise(x + 1, y) + getNoise(x, y - 1) + getNoise(x, y + 1)) / 8.0f;
	double center = getNoise(x, y) / 4.0f;
	return corners + sides + center;
}

double SimplexNoise::getNoise(int x, int y)
{
	/*double result = 0;
	for (int i = 0; i < octaves.size(); i++) {
		double frequency = pow(2, i);
		double amplitude = pow(persistence, octaves.size() - 1);

		result += octaves[i].noise(x / frequency, y / frequency)*amplitude;
	}
	return result;*/
	std::mt19937 mt_rand(x * 2435 + y * 34245 + seed);
	auto real_rand = std::bind(std::uniform_real_distribution<double>(-1, 1), mt_rand);
	return real_rand();
}
