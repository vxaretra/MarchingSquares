#pragma once

#include <vector>
#include "PerlinNoise.h"

class MarchingSquares
{
public:
	MarchingSquares();
	~MarchingSquares();

	void update();
	void draw();

private:
	int getState(int a, int b, int c, int d);

	const int width = 800;
	const int height = 600;
	const int res = 20;
	const int col = width / res + 1;
	const int row = height / res + 1;
	float threshold = 0.5f;
	float zCounter = 0.1f;

	std::vector<std::vector<float>> field;
	siv::PerlinNoise perlin;
};
