#pragma once
#include <array>
#include <math.h>
#include <initializer_list>
#include "vector.h"

// look at https://webglfundamentals.org/webgl/lessons/webgl-3d-orthographic.html 
namespace onodrim {


	class Matrix4
	{
	public:
		Matrix4() : m_Values({
				1, 0, 0, 0, 
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			})
		{

		}
		Matrix4(const std::initializer_list<float> list)
		{
			this->operator=(list);
		}
		~Matrix4()
		{

		}

	private:
#define M00 0
#define M01 1
#define M02 2
#define M03 3
#define M10 4
#define M11 5
#define M12 6
#define M13 7
#define M20 8
#define M21 9
#define M22 10
#define M23 11
#define M30 12
#define M31 13
#define M32 14
#define M33 15
	public:

		float* GetArray()
		{
			return m_Values.data();
		}

		Matrix4 static MakeIdentity()
		{
			return { 
				1, 0, 0, 0, 
				0, 1, 0, 0, 
				0, 0, 1, 0, 
				0, 0, 0, 1 
			};
		}
		Matrix4 static MakeZero()
		{
			return {
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0
			};
		}

		inline Matrix4& Identity()
		{
			m_Values = {
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			};
			return *this;
		}

		inline Matrix4& Zero()
		{
			memset(&m_Values, 0, sizeof(float) * 16);
			return *this;
		}

		inline Matrix4& Multiply(Matrix4& multiply)
		{
			const float a00 = m_Values[M00];
			const float a01 = m_Values[M01];
			const float a02 = m_Values[M02];
			const float a03 = m_Values[M03];
			const float a10 = m_Values[M10];
			const float a11 = m_Values[M11];
			const float a12 = m_Values[M12];
			const float a13 = m_Values[M13];
			const float a20 = m_Values[M20];
			const float a21 = m_Values[M21];
			const float a22 = m_Values[M22];
			const float a23 = m_Values[M23];
			const float a30 = m_Values[M30];
			const float a31 = m_Values[M31];
			const float a32 = m_Values[M32];
			const float a33 = m_Values[M33];
			const float b00 = multiply.m_Values[M00];
			const float b01 = multiply.m_Values[M01];
			const float b02 = multiply.m_Values[M02];
			const float b03 = multiply.m_Values[M03];
			const float b10 = multiply.m_Values[M10];
			const float b11 = multiply.m_Values[M11];
			const float b12 = multiply.m_Values[M12];
			const float b13 = multiply.m_Values[M13];
			const float b20 = multiply.m_Values[M20];
			const float b21 = multiply.m_Values[M21];
			const float b22 = multiply.m_Values[M22];
			const float b23 = multiply.m_Values[M23];
			const float b30 = multiply.m_Values[M30];
			const float b31 = multiply.m_Values[M31];
			const float b32 = multiply.m_Values[M32];
			const float b33 = multiply.m_Values[M33];
			m_Values = {
				(a00 * b00) + (a01 * b10) + (a02 * b20) + (a03 * b30),
				(a00 * b01) + (a01 * b11) + (a02 * b21) + (a03 * b31),
				(a00 * b02) + (a01 * b12) + (a02 * b22) + (a03 * b32),
				(a00 * b03) + (a01 * b13) + (a02 * b23) + (a03 * b33),
				(a10 * b00) + (a11 * b10) + (a12 * b20) + (a13 * b30),
				(a10 * b01) + (a11 * b11) + (a12 * b21) + (a13 * b31),
				(a10 * b02) + (a11 * b12) + (a12 * b22) + (a13 * b32),
				(a10 * b03) + (a11 * b13) + (a12 * b23) + (a13 * b33),
				(a20 * b00) + (a21 * b10) + (a22 * b20) + (a23 * b30),
				(a20 * b01) + (a21 * b11) + (a22 * b21) + (a23 * b31),
				(a20 * b02) + (a21 * b12) + (a22 * b22) + (a23 * b32),
				(a20 * b03) + (a21 * b13) + (a22 * b23) + (a23 * b33),
				(a30 * b00) + (a31 * b10) + (a32 * b20) + (a33 * b30),
				(a30 * b01) + (a31 * b11) + (a32 * b21) + (a33 * b31),
				(a30 * b02) + (a31 * b12) + (a32 * b22) + (a33 * b32),
				(a30 * b03) + (a31 * b13) + (a32 * b23) + (a33 * b33)
			};
			return *this;
		}

		inline Matrix4& Translate(float x, float y, float z)
		{
			const float a00 = m_Values[M00];
			const float a01 = m_Values[M01];
			const float a02 = m_Values[M02];
			const float a03 = m_Values[M03];
			const float a10 = m_Values[M10];
			const float a11 = m_Values[M11];
			const float a12 = m_Values[M12];
			const float a13 = m_Values[M13];
			const float a20 = m_Values[M20];
			const float a21 = m_Values[M21];
			const float a22 = m_Values[M22];
			const float a23 = m_Values[M23];
			const float a30 = m_Values[M30];
			const float a31 = m_Values[M31];
			const float a32 = m_Values[M32];
			const float a33 = m_Values[M33];
			const float b30 = x;
			const float b31 = y;
			const float b32 = z;
			m_Values = {
				(a00) + (a03 * b30),
				(a01) + (a03 * b31),
				(a02) + (a03 * b32),
				(a03),
				(a10) + (a13 * b30),
				(a11) + (a13 * b31),
				(a12) + (a13 * b32),
				(a13),
				(a20) + (a23 * b30),
				(a21) + (a23 * b31),
				(a22) + (a23 * b32),
				(a23),
				(a30) + (a33 * b30),
				(a31) + (a33 * b31),
				(a32) + (a33 * b32),
				(a33)
			};
			return *this;
		}

		inline Matrix4& Translate(Vector<float, 3> translation)
		{
			return Translate(translation[0], translation[1], translation[2]);
		}

		inline Matrix4& Scale(float x, float y, float z)
		{
			const float a00 = m_Values[M00];
			const float a01 = m_Values[M01];
			const float a02 = m_Values[M02];
			const float a03 = m_Values[M03];
			const float a10 = m_Values[M10];
			const float a11 = m_Values[M11];
			const float a12 = m_Values[M12];
			const float a13 = m_Values[M13];
			const float a20 = m_Values[M20];
			const float a21 = m_Values[M21];
			const float a22 = m_Values[M22];
			const float a23 = m_Values[M23];
			const float a30 = m_Values[M30];
			const float a31 = m_Values[M31];
			const float a32 = m_Values[M32];
			const float a33 = m_Values[M33];
			const float b00 = x;
			const float b11 = y;
			const float b22 = z;
			m_Values = {
				(a00 * b00),
				(a01 * b11),
				(a02 * b22),
				(a03),
				(a10 * b00),
				(a11 * b11),
				(a12 * b22),
				(a13),
				(a20 * b00),
				(a21 * b11),
				(a22 * b22),
				(a23),
				(a30 * b00),
				(a31 * b11),
				(a32 * b22),
				(a33)
			};
			return *this;
		}

		inline Matrix4& Scale(Vector<float, 3> scale)
		{
			return Scale(scale[0], scale[1], scale[2]);
		}

		inline Matrix4& Scalar(float scalar)
		{
			return Scale(scalar, scalar, scalar);
		}

		Matrix4& operator*=(Matrix4& multiply)
		{
			return this->Multiply(multiply);
		}

		bool operator==(Matrix4& toCompare)
		{
			return memcmp(&m_Values, &toCompare.m_Values, 16 * sizeof(float)) == 0;
		}
		void operator=(Matrix4& toCopy)
		{
			memcpy(&m_Values, &toCopy, 16*sizeof(float));
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
		std::array<float, 16> m_Values;

	};
}
