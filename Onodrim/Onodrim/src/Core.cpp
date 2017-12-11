#include <chrono>
#include <iostream>
#include <thread>
#include "./Core.h"
#include "./utils/Time.h"
#include "./utils/Logger.h"
#include "./system/SystemManager.h"
#include "./system/update/FixedUpdateSystem.h"
#include "./system/update/UpdateSystem.h"
#include "./system/render/OpenGLSystem.h"
#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif
namespace onodrim {
	Core::Core()
	{
		utils::log("Core created.");
		system::SystemManager::GetInstance()->AddSystem(new system::update::FixedUpdateSystem());
		system::SystemManager::GetInstance()->AddSystem(new system::update::UpdateSystem());
		system::SystemManager::GetInstance()->AddSystem(new system::render::OpenGLSystem());
	}


	Core::~Core()
	{
	}

	void Core::Start() { 
		utils::log("Core started.");

		#ifdef __EMSCRIPTEN__
			// need to figure out how to do this...
			// emscripten_set_main_loop(this->*Some_fnc_ptr, 0, 1);
		#else
			while (true)
			{
				GameLoop();
			}
		#endif
		
		
	}

	void Core::GameLoop() {
		Update();
		Render();
		// std::this_thread::sleep_for(std::chrono::duration<float>(1.f/60.f));
	}

	void Core::Update() {
		system::SystemManager::GetInstance()->Tick();
	}

	void Core::Render() {

	}
}
