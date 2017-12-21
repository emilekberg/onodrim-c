#include "./systemManager.h"
#include "../utils/logger.h"
namespace onodrim::system {
	SystemManager::SystemManager()
	{
		LOG_INFO("SystemManager created");
	}


	SystemManager::~SystemManager()
	{
	}

	void SystemManager::RemoveComponentInstance(Component* component)
	{

	}
	void SystemManager::AddSystem(TickSystem* system)
	{
		LOG_INFO("SystemManager::AddSystem(%s);", typeid(system).name());
		this->m_TickSystems.push_back(system);
		this->AddSystem(static_cast<BaseSystem*>(system));
	}
	void SystemManager::AddSystem(BaseSystem* system)
	{
		this->m_Systems.push_back(system);
	}
}

