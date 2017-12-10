#pragma once
#include "./Component.h"
namespace onodrim {
	class FixedUpdateComponent : public Component
	{
	public:
		FixedUpdateComponent() {};
		virtual ~FixedUpdateComponent() {};

		virtual void FixedUpdate(bool compensate) = 0;
	};


}
