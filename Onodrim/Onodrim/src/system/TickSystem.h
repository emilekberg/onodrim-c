#pragma once
#include "./BaseSystem.h"
namespace onodrim::system {
	class TickSystem : public BaseSystem
	{
	public:
		inline virtual void Tick() = 0;
	};
}
