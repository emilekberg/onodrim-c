#include <chrono>
#include <iostream>
#include <thread>
#include "./Core.h"
#include "./utils/Time.h"
#include "./utils/Logger.h"
#include "./system/SystemManager.h"
#include "./system/FixedUpdateSystem.h"
#include "./system/UpdateSystem.h"
#include "./system/OpenGLSystem.h"

namespace onodrim {
	Core::Core()
	{
		utils::logLine("Core created.");
		system::SystemManager::GetInstance()->AddSystem(new system::FixedUpdateSystem());
		system::SystemManager::GetInstance()->AddSystem(new system::UpdateSystem());
		system::SystemManager::GetInstance()->AddSystem(new system::OpenGLSystem());
	}


	Core::~Core()
	{
	}

	void Core::Start() { 
		utils::logLine("Core started.");

		while (true)
		{
			GameLoop();
		}
		
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
