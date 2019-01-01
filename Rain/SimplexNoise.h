#pragma once

#include <math.h>
#include <random>
#include <iostream>
#include <functional> 

#include "Noise.h"

class SimplexNoise
{
public:
	SimplexNoise(int numberOfOctaves, double persistence, int seed);
	SimplexNoise();
	SimplexNoise(int seed);
	~SimplexNoise();
	double getInterpolatedNoise(float x, float z);
	double getSmoothNoise(int x, int y);
	double getNoise(int x, int y);
private:
	double persistence;
	int numberOfOctaves;
	int seed;
	std::vector<NoiseOctave> octaves;
};

