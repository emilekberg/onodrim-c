#pragma once
#include <math.h>
namespace onodrim {
	class Vector2
	{
	public:
		Vector2() : Vector2(0, 0) {};
		Vector2(Vector2& toCopy) : Vector2::Vector2(toCopy.X, toCopy.Y) {}
		Vector2(float x, float y)
		{
			X = x;
			Y = y;
		}

		~Vector2()
		{
	
		}

		inline float Length()
		{
			return sqrt((X * X) + (Y * Y));
		}
		inline float LengthSquared()
		{
			return (X * X) + (Y * Y);
		}
		inline Vector2& Normalize()
		{
			return this->operator/=(Length());
		}

	public:
		float X;
		float Y;

		Vector2 operator+(const Vector2& toAdd)
		{
			return (Vector2(X + toAdd.X, Y + toAdd.Y));
		}
		Vector2 operator-(const Vector2& toSubtract)
		{
			return Vector2(X - toSubtract.X, Y - toSubtract.Y);
		}
		Vector2 operator*(const Vector2& toMultiply)
		{
			return Vector2(X * toMultiply.X, Y * toMultiply.Y);
		}
		friend Vector2 operator*(const float factor, Vector2& v)
		{
			return Vector2(v.X * factor, v.Y * factor);
		}
		Vector2 operator*(const float factor)
		{
			return Vector2(X * factor, Y * factor);
		}
		Vector2 operator/(const Vector2& toDivide)
		{
			return Vector2(X / toDivide.X, Y / toDivide.Y);
		}
		friend Vector2 operator/(const float divisor, Vector2& v)
		{
			return Vector2(v.X / divisor, v.Y / divisor);
		}
		Vector2 operator/(const float divisor)
		{
			return Vector2(X / divisor, Y / divisor);
		}
		Vector2& operator+=(const Vector2& toAdd)
		{
			X += toAdd.X;
			Y += toAdd.Y;
			return *this;
		}
		Vector2& operator-=(const Vector2& toSubtract)
		{
			X -= toSubtract.X;
			Y -= toSubtract.Y;
			return *this;
		}
		Vector2& operator*=(const Vector2& toMultiply)
		{
			X *= toMultiply.X;
			Y *= toMultiply.Y;
			return *this;
		}
		Vector2& operator*=(const float& factor)
		{
			X *= factor;
			Y *= factor;
			return *this;
		}
		Vector2& operator/=(const Vector2& toDivide)
		{
			X /= toDivide.X;
			Y /= toDivide.Y;
			return *this;
		}
		Vector2& operator/=(const float& divisor)
		{
			X /= divisor;
			Y /= divisor;
			return *this;
		}
		Vector2& operator=(const Vector2& toCopy)
		{
			X = toCopy.X;
			Y = toCopy.Y;
			return *this;
		}
		bool operator==(const Vector2& toCompare)
		{
			return X == toCompare.X && Y == toCompare.Y;
		}
	};
}
