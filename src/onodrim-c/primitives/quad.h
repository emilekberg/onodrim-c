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
	const unsigned char Indices[6]{
		0, 1, 2,
		0, 2, 3
	};

	const unsigned char TextureCoordinates[8]{
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};
};

