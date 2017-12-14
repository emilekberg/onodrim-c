#include "./systemManager.h"
#include "../utils/logger.h"
namespace onodrim::system {
	SystemManager::SystemManager()
	{
		utils::log("SystemManager created");
	}


	SystemManager::~SystemManager()
	{
	}

	void SystemManager::RemoveComponentInstance(Component* component)
	{

	}
	void SystemManager::AddSystem(TickSystem* system)
	{
		std::string test = typeid(system).name();
		utils::log("SystemManager::AddSystem(" + test + ");");
		this->m_TickSystems.push_back(system);
		this->AddSystem(static_cast<BaseSystem*>(system));
	}
	void SystemManager::AddSystem(BaseSystem* system)
	{
		this->m_Systems.push_back(system);
	}
}

