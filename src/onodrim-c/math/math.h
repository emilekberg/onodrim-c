#pragma once
#include "./matrix3.h"
namespace onodrim::math
{
	float lerp(const float start, const float end, const float delta)
	{
		return start + delta * (end - start);
	}

	void matrixLerp(Matrix3& target, Matrix3& a, Matrix3& b, const float delta)
	{
		for (int i = 0; i < 9; ++i)
		{
			target[i] = lerp(a[i], b[i], delta);
		}
	}
}