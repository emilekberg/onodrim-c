#pragma once
#include "./component.h"
namespace onodrim {
	class UpdateComponent : public Component
	{
	public:
		UpdateComponent(Entity* pEntity) : Component(pEntity) {};
		virtual ~UpdateComponent() {};

		virtual void Update() = 0;
	};


}
