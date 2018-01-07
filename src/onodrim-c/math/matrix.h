#pragma once
#include <array>
#include <math.h>
#include <initializer_list>
namespace onodrim {
	template <typename T, unsigned int SIZE>
	class Matrix
	{
	public:
		Matrix()
		{
			Identity();
		}
		Matrix(const float* values)
		{
			for (int i = 0; i < 9; i++) {
				m_Values[i] = values[i];
			}
		}
		Matrix(const std::initializer_list<T> list)
		{
			this->operator=(list);
		}
		~Matrix()
		{

		}

		float* GetArray()
		{
			return m_Values.data();
		}

		Matrix static MakeIdentity()
		{
			return Matrix().Identity();
		}
		Matrix static MakeZero()
		{
			return Matrix().Zero();
		}

		inline Matrix& Identity()
		{
			for (int i = 0; i < SIZE*SIZE; ++i)
			{
				if ((int)(i / (float)SIZE) == i % SIZE)
				{
					m_Values[i] = 1;
				}
				else
				{
					m_Values[i] = 0;
				}
			}
			return *this;
		}

		inline Matrix& Zero()
		{
			memset(&m_Values, 0, SIZE * SIZE * sizeof(T));
		}

		inline Matrix& Multiply(const std::array<float, 9>& mul)
		{
			for (let i = 0; i < SIZE; ++i)
			{
				for (let j = 0; j < SIZE; ++j)
				{
					for (let k = 0; k < SIZE; ++k)
					{
						c[i * size + j] += a[i * size + k] * b[k * size + j];
					}
				}
			}

			const float a00 = m_Values[0];
			const float a01 = m_Values[1];
			const float a02 = m_Values[2];
			const float a10 = m_Values[3];
			const float a11 = m_Values[4];
			const float a12 = m_Values[5];
			const float a20 = m_Values[6];
			const float a21 = m_Values[7];
			const float a22 = m_Values[8];
			const float b00 = mul[0];
			const float b01 = mul[1];
			const float b02 = mul[2];
			const float b10 = mul[3];
			const float b11 = mul[4];
			const float b12 = mul[5];
			const float b20 = mul[6];
			const float b21 = mul[7];
			const float b22 = mul[8];
			m_Values = {
				(a00 * b00) + (a01 * b10) + (a02 * b20),
				(a00 * b01) + (a01 * b11) + (a02 * b21),
				(a00 * b02) + (a01 * b12) + (a02 * b22),
				(a10 * b00) + (a11 * b10) + (a12 * b20),
				(a10 * b01) + (a11 * b11) + (a12 * b21),
				(a10 * b02) + (a11 * b12) + (a12 * b22),
				(a20 * b00) + (a21 * b10) + (a22 * b20),
				(a20 * b01) + (a21 * b11) + (a22 * b21),
				(a20 * b02) + (a21 * b12) + (a22 * b22)
			};
			return *this;
		}
		inline Matrix& Multiply(Matrix& mul)
		{
			return this->Multiply(mul.m_Values);
		}

		/*
		c,-s,0,
		s,c,0,
		0,0,1
		*/
		inline Matrix& Rotate(float rotation)
		{
			const float s = sin(rotation);
			const float c = cos(rotation);
			const float a00 = m_Values[0];
			const float a01 = m_Values[1];
			const float a02 = m_Values[2];
			const float a10 = m_Values[3];
			const float a11 = m_Values[4];
			const float a12 = m_Values[5];
			const float a20 = m_Values[6];
			const float a21 = m_Values[7];
			const float a22 = m_Values[8];
			const float b00 = c;
			const float b01 = -s;
			const float b10 = s;
			const float b11 = c;
			const float b22 = 1;
			m_Values = {
				(a00 * b00) + (a01 * b10),
				(a00 * b01) + (a01 * b11),
				(a02 * b22),
				(a10 * b00) + (a11 * b10),
				(a10 * b01) + (a11 * b11),
				(a12 * b22),
				(a20 * b00) + (a21 * b10),
				(a20 * b01) + (a21 * b11),
				(a22 * b22)
			};
			return *this;
		}
		/*
		1,0,0
		0,1,0
		x,y,1
		*/
		inline Matrix& Translate(float x, float y)
		{
			const float a00 = m_Values[0];
			const float a01 = m_Values[1];
			const float a02 = m_Values[2];
			const float a10 = m_Values[3];
			const float a11 = m_Values[4];
			const float a12 = m_Values[5];
			const float a20 = m_Values[6];
			const float a21 = m_Values[7];
			const float a22 = m_Values[8];
			const float b00 = 1;
			const float b01 = 0;
			const float b11 = 1;
			const float b20 = x;
			const float b21 = y;
			const float b22 = 1;
			m_Values = {
				(a00 * b00) + (a02 * b20),
				(a00 * b01) + (a01 * b11) + (a02 * b21),
				(a02 * b22),
				(a10 * b00) + (a12 * b20),
				(a10 * b01) + (a11 * b11) + (a12 * b21),
				(a12 * b22),
				(a20 * b00) + (a22 * b20),
				(a20 * b01) + (a21 * b11) + (a22 * b21),
				(a22 * b22)
			};
			return *this;
		}

		/*
		x,0,0,
		0,y,0,
		0,0,1
		*/
		inline Matrix& Scale(float x, float y)
		{
			const float a00 = m_Values[0];
			const float a01 = m_Values[1];
			const float a02 = m_Values[2];
			const float a10 = m_Values[3];
			const float a11 = m_Values[4];
			const float a12 = m_Values[5];
			const float a20 = m_Values[6];
			const float a21 = m_Values[7];
			const float a22 = m_Values[8];
			const float b00 = x;
			const float b11 = y;
			const float b22 = 1;
			m_Values = {
				(a00 * b00),
				(a01 * b11),
				(a02 * b22),
				(a10 * b00),
				(a11 * b11),
				(a12 * b22),
				(a20 * b00),
				(a21 * b11),
				(a22 * b22)
			};
			return *this;
		}

		Matrix& operator*=(Matrix& mul)
		{
			return this->Multiply(mul.m_Values);
		}

		bool operator==(Matrix& toCompare)
		{
			return memcmp(&m_Values, &toCompare.m_Values, SIZE*SIZE * sizeof(T)) == 0;
		}
		void operator=(Matrix& toCopy)
		{
			memcpy(&m_Values, &toCopy, SIZE*SIZE*sizeof(T));
		}
		float& operator[](int index)
		{
			return m_Values[index];
		}

	private:
		T m_Values[SIZE*SIZE];

	};
}
