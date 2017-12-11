#pragma once
#include "../math/Matrix3.h"
namespace onodrim::data
{
	struct RenderState
	{
		bool WasDirty = true;
		Matrix3 Matrix;
		float Alpha = 1.0;
	};
}
