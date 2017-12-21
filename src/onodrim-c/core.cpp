#include <chrono>
#include <iostream>
#include <thread>
#include "./core.h"
#include "./utils/time.h"
#include "./utils/logger.h"
#include "./system/systemManager.h"
#include "./system/update/fixedUpdateSystem.h"
#include "./system/update/updateSystem.h"
#include "./system/render/openGLSystem.h"
#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif
namespace onodrim {
	Core::Core()
	{
		LOG_INFO("Core created.");
		system::SystemManager::GetInstance()->AddSystem(new system::update::FixedUpdateSystem());
		system::SystemManager::GetInstance()->AddSystem(new system::update::UpdateSystem());
		system::SystemManager::GetInstance()->AddSystem(new system::render::OpenGLSystem());
	}


	Core::~Core()
	{
	
	}

	void Core::Start() {
		LOG_INFO("Core started.");

#ifdef __EMSCRIPTEN__
		// need to figure out how to do this...
		// emscripten_set_main_loop(this->*Some_fnc_ptr, 0, 1);
#else
		while (GameLoop()) {};
#endif
	}

	bool Core::GameLoop() {
		return system::SystemManager::GetInstance()->Tick();
	}
}
