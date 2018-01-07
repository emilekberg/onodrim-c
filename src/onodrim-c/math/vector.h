#pragma once
#include <math.h>
#include <array>
#include <initializer_list>
namespace onodrim {
	template <typename T, unsigned int SIZE>
	class Vector
	{
	public:
		Vector()
		{
			memset(&m_Values, 0, sizeof(T)*SIZE);
		}
		Vector(const std::initializer_list<T> list)
		{
			this->operator=(list);
		}
		~Vector()
		{

		}

		inline T Length()
		{
			return static_cast<T>(sqrt(this->LengthSquared()));
		}
		inline T LengthSquared()
		{
			T sum = 0;
			for (int i = 0; i < SIZE; ++i)
			{
				sum += m_Values[i] * m_Values[i];
			}
			return sum;
		}
		inline Vector& Normalize()
		{
			return this->operator/=(Length());
		}

	private:
		T m_Values[SIZE];

	public:
		T& operator[](const int index)
		{
			return m_Values[index];
		}
		Vector<T, SIZE> operator+(const Vector<T, SIZE>& toAdd)
		{
			Vector<T, SIZE> ret;
			for (int i = 0; i < SIZE; ++i)
			{
				ret.m_Values[i] = m_Values[i] + toAdd.m_Values[i];
			}
			return ret;
		}
		Vector<T, SIZE> operator-(const Vector<T, SIZE>& toSubtract)
		{
			Vector<T, SIZE> ret;
			for (int i = 0; i < SIZE; ++i)
			{
				ret[i] = m_Values[i] - toSubtract.m_Values[i];
			}
			return ret;
		}
		Vector<T, SIZE> operator*(const Vector<T, SIZE>& toSubtract)
		{
			Vector<T, SIZE> ret;
			for (int i = 0; i < SIZE; ++i)
			{
				ret[i] = m_Values[i] * toSubtract.m_Values[i];
			}
			return ret;
		}
		friend Vector<T, SIZE> operator*(const float factor, Vector<T, SIZE>& v)
		{
			Vector<T, SIZE> ret;
			for (int i = 0; i < SIZE; ++i)
			{
				ret[i] =v[i] * factor;
			}
			return ret;
		}
		Vector<T, SIZE> operator*(const float factor)
		{
			Vector<T, SIZE> ret;
			for (int i = 0; i < SIZE; ++i)
			{
				ret[i] = m_Values[i] * factor;
			}
			return ret;
		}
		Vector<T, SIZE> operator/(const Vector<T, SIZE>& toDivide)
		{
			Vector<T, SIZE> ret;
			for (int i = 0; i < SIZE; ++i)
			{
				ret[i] = m_Values[i] / toDivide.m_Values[i];
			}
			return ret;
		}
		friend Vector<T, SIZE> operator/(const float divisor, Vector<T, SIZE>& v)
		{
			Vector<T, SIZE> ret;
			for (int i = 0; i < SIZE; ++i)
			{
				ret[i] = v[i] / divisor;
			}
			return ret;
		}
		Vector<T, SIZE> operator/(const float divisor)
		{
			Vector<T, SIZE> ret;
			for (int i = 0; i < SIZE; ++i)
			{
				ret[i] = m_Values[i] / divisor;
			}
			return ret;
		}
		Vector<T, SIZE>& operator+=(const Vector<T, SIZE>& toAdd)
		{
			for (int i = 0; i < SIZE; ++i)
			{
				m_Values[i] += toAdd.m_Values[i];
			}
			return *this;
		}
		Vector<T, SIZE>& operator-=(const Vector<T, SIZE>& toSubtract)
		{
			for (int i = 0; i < SIZE; ++i)
			{
				m_Values[i] -= toSubtract.m_Values[i];
			}
			return *this;
		}
		Vector<T, SIZE>& operator*=(const Vector<T, SIZE>& toMultiply)
		{
			for (int i = 0; i < SIZE; ++i)
			{
				m_Values[i] *= toMultiply.m_Values[i];
			}
			return *this;
		}
		Vector<T, SIZE>& operator*=(const float& factor)
		{
			for (int i = 0; i < SIZE; ++i)
			{
				m_Values[i] *= factor;
			}
			return *this;
		}
		Vector<T, SIZE>& operator/=(const Vector<T, SIZE>& toDivide)
		{
			for (int i = 0; i < SIZE; ++i)
			{
				m_Values[i] /= toDivide.m_Values[i];
			}
			return *this;
		}
		Vector<T, SIZE>& operator/=(const float& divisor)
		{
			for (int i = 0; i < SIZE; ++i)
			{
				m_Values[i] /= divisor;
			}
			return *this;
		}
		Vector<T, SIZE>& operator=(const Vector<T, SIZE>& toCopy)
		{
			memcpy(&m_Values, toCopy.m_Values, sizeof(T) * SIZE);
			return *this;
		}
		Vector<T, SIZE>& operator=(const std::initializer_list<T> list)
		{
			int count = 0;
			for (auto &value : list)
			{
				m_Values[count] = value;
				++count;
			}
			return *this;
		}
		bool operator==(const Vector<T, SIZE>& toCompare)
		{
			return memcmp(&m_Values, toCompare.m_Values, sizeof(T) * SIZE) == 0;
		}
	};
}
