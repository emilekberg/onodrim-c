#pragma once
#include "./Component.h"
namespace onodrim {
	class UpdateComponent : public Component
	{
	public:
		UpdateComponent() {};
		virtual ~UpdateComponent() {};

		virtual void Update() = 0;
	};


}
