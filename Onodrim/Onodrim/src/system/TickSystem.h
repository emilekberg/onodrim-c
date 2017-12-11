#pragma once
#include "./BaseSystem.h"
namespace onodrim::system {
	class TickSystem : public BaseSystem
	{
	public:
		inline virtual bool Tick() = 0;
	};
}
