#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>

#include "Helper.h"

#include <cstdint>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>

const int NUMBER_OF_SWAPS = 400;

struct Grad {
	double x, y, z, w;

	Grad(double xi, double yi, double zi)
	{
		x = xi;
		y = yi;
		z = zi;
	}

	Grad(double xi, double yi, double zi, double wi)
	{
		x = xi;
		y = yi;
		z = zi;
		w = wi;
	}
};


class NoiseOctave
{
public:
	NoiseOctave(int seed);
	~NoiseOctave();
	double noise(double xin, double yin);
	
private: 
	int seed;
	static uint8_t p_supply[];
	static Grad grad3[];
	static const double F2;
	static const double G2;
	uint8_t p[512];
	uint8_t perm[512];
	uint8_t permMod12[512];
};

