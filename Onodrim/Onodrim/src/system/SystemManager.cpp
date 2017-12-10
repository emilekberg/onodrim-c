#include "./SystemManager.h"
#include "../utils/Logger.h"
namespace onodrim::system {
	SystemManager::SystemManager()
	{
		utils::logLine("SystemManager created");
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
		utils::logLine("SystemManager::AddSystem(" + test + ");");
		this->m_TickSystems.push_back(system);
		this->AddSystem(static_cast<BaseSystem*>(system));
	}
	void SystemManager::AddSystem(BaseSystem* system)
	{
		this->m_Systems.push_back(system);
	}
}

