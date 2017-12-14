#pragma once
#include "./component.h"
namespace onodrim {
	class FixedUpdateComponent : public Component
	{
	public:
		FixedUpdateComponent(Entity* pEntity) : Component(pEntity) {};
		virtual ~FixedUpdateComponent() {};

		virtual void FixedUpdate(bool compensate) = 0;
	};


}
