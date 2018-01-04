#pragma once
#include <array>
class Quad
{
public:
	Quad(){}
	virtual ~Quad(){}

	const float Vertices[8]{
		-1, -1,
		-1, 1,
		1, 1,
		1, -1
	};
	const unsigned short Indices[6]{
		0, 1, 2,
		0, 2, 3
	};

	const unsigned short TextureCoordinates[8]{
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};
};

