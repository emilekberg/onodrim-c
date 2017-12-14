#pragma once
#include <stdlib.h>
#include <math.h>
namespace onodrim::random {
	inline int Int(int max)
	{
		return rand() % max;
	}
	inline int Int(int min, int max)
	{
		return min + (rand() % (max - min));
	}
	inline float Float()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}
	inline float Float(float max)
	{
		return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * max;
	}
	inline float Float(float min, float max)
	{
		return min + ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (max-min));
	}


	void Seed(int number)
	{
		srand(number);
	}
}