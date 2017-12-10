#pragma once
#include <chrono>
namespace onodrim::time {
	static auto __lastUpdateTime = std::chrono::high_resolution_clock::now();
	static auto __started = std::chrono::high_resolution_clock::now();
	static float __deltaTime = 1;

	inline void update()
	{
		auto now = std::chrono::high_resolution_clock::now();
		__deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - __lastUpdateTime).count();
		__lastUpdateTime = now;
	}
	inline float now()
	{
		auto now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::duration<float>>(now - __started).count();
	}

	inline void setFixedUpdateTimeStep(float timestep)
	{
		__deltaTime = timestep;
	}

	inline float deltaTime()
	{
		return __deltaTime;
	}

	inline float deltaTimeMS()
	{
		return __deltaTime / 1000.f;
	}

	inline int fps()
	{
		return 1.0f / __deltaTime;
	}
}