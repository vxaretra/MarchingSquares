#pragma once

#include "MarchingSquares.h"

class Application
{
public:
	Application();
	~Application();

	void run();

private:
	const int width = 800;
	const int height = 600;

	MarchingSquares marchingSquares;
};
