#include "Params.h"
#include <iostream>
#include <fstream>

Params* Params::instancePtr = nullptr;

Params::Params()
{
	init("params.txt");
}

bool Params::init(const std::string &filename)
{
	char file[256];
	sprintf_s(file, filename.c_str());
	std::fstream fin (file, std::ios_base::in);

	if (!fin.is_open())
		return false;

	char buffer[50];

	fin >> buffer;
	fin >> neighbourTagRadius;
	fin >> buffer;
	fin >> wallWeight;
	fin >> buffer;
	fin >> evadeWeight;
	fin >> buffer;
	fin >> wanderWeight;	
	fin >> buffer;
	fin >> separationWeight;
	fin >> buffer;
	fin >> separationForce;
	fin >> buffer;
	fin >> alignmentWeight;
	fin >> buffer;
	fin >> cohesionWeight;
	fin >> buffer;
	fin >> feelerLength;
	fin >> buffer;
	fin >> feelerAngle;
	fin >> buffer;
	fin >> panicDistance;
	fin >> buffer;
	fin >> wanderRate;
	fin >> buffer;
	fin >> wanderDistance;
	fin >> buffer;
	fin >> wanderRadius;
	fin >> buffer;
	fin >> windowX;
	fin >> buffer;
	fin >> windowY;
	fin >> buffer;

	fin.clear();
	fin.close();
	return true;
}
