#pragma once
#include <array>
#include <math.h>
namespace onodrim {
	class Matrix3
	{
	public:
		Matrix3() : m_Values({ 
				1, 0, 0, 
				0, 1, 0, 
				0, 0, 1 
			})
		{

		}
		Matrix3(const std::initializer_list<float> list)
		{
			this->operator=(list);
		}
		~Matrix3()
		{

		}

		float* GetArray()
		{
			return m_Values.data();
		}

		Matrix3 static MakeIdentity()
		{
			return { 
				1, 0, 0, 
				0, 1, 0, 
				0, 0, 1 
			};
		}
		Matrix3 static MakeZero()
		{
			return {
				0, 0, 0,
				0, 0, 0,
				0, 0, 0
			};
		}

		inline Matrix3& Identity()
		{
			m_Values = {
				1,0,0,
				0,1,0,
				0,0,1
			};
			return *this;
		}

		inline Matrix3& Multiply(Matrix3& multiply)
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
			const float b00 = multiply.m_Values[0];
			const float b01 = multiply.m_Values[1];
			const float b02 = multiply.m_Values[2];
			const float b10 = multiply.m_Values[3];
			const float b11 = multiply.m_Values[4];
			const float b12 = multiply.m_Values[5];
			const float b20 = multiply.m_Values[6];
			const float b21 = multiply.m_Values[7];
			const float b22 = multiply.m_Values[8];
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

		/*
		c,-s,0,
		s,c,0,
		0,0,1
		*/
		inline Matrix3& Rotate(float rotation)
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
			m_Values = {
				(a00 * b00) + (a01 * b10),
				(a00 * b01) + (a01 * b11),
				(a02),
				(a10 * b00) + (a11 * b10),
				(a10 * b01) + (a11 * b11),
				(a12),
				(a20 * b00) + (a21 * b10),
				(a20 * b01) + (a21 * b11),
				(a22)
			};
			return *this;
		}
		/*
		1,0,0
		0,1,0
		x,y,1
		*/
		inline Matrix3& Translate(float x, float y)
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
			const float b20 = x;
			const float b21 = y;
			m_Values = {
				(a00) + (a02 * b20),
				(a01) + (a02 * b21),
				(a02),
				(a10) + (a12 * b20),
				(a11) + (a12 * b21),
				(a12),
				(a20) + (a22 * b20),
				(a21) + (a22 * b21),
				(a22)
			};
			return *this;
		}

		/*
		x,0,0,
		0,y,0,
		0,0,1
		*/
		inline Matrix3& Scale(float x, float y)
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
			m_Values = {
				(a00 * b00),
				(a01 * b11),
				(a02),
				(a10 * b00),
				(a11 * b11),
				(a12),
				(a20 * b00),
				(a21 * b11),
				(a22)
			};
			return *this;
		}

		Matrix3& operator*=(Matrix3& multiply)
		{
			return this->Multiply(multiply);
		}

		bool operator==(Matrix3& toCompare)
		{
			return memcmp(&m_Values, &toCompare.m_Values, 36) == 0;
		}
		void operator=(Matrix3& toCopy)
		{
			memcpy(&m_Values, &toCopy, 36);
		}
		void operator=(const std::initializer_list<float> list)
		{
			int count = 0;
			for (float value : list)
			{
				m_Values[count++] = value;
			}
		}
		float& operator[](int index)
		{
			return m_Values[index];
		}

	private:
		std::array<float, 9> m_Values;

	};
}
