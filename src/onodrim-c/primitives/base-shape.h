#pragma once
#include <array>
template <typename T, unsigned int SIZE>
class BaseShape
{
public:
	BaseShape();
	virtual ~BaseShape();


protected:
	std::array<T, SIZE> m_Vertices;
	std::array<T, SIZE> m_Indices;
};

