#pragma once
template <typename T>
class Rect
{
public:
	Rect(T x, T y, T w, T h)
	{
		X = x;
		Y = y;
		W = w;
		H = h;
	}
	Rect()
	{
		X = 0;
		Y = 0;
		W = 0;
		H = 0;
	}
	~Rect()
	{

	}

	Vector2& operator=(const Vector2& toCopy)
	{
		X = toCopy.X;
		Y = toCopy.Y;
		W = toCopy.W;
		H = toCopy.H;
		return *this;
	}

	bool operator==(const Rect& toCompare)
	{
		return X == toCompare.X && Y == toCompare.Y && W == toCompare.W && H == toCompare.H;
	}

	T X;
	T Y;
	T W;
	T H;
};