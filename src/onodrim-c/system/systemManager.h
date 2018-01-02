#pragma once
#include <vector>
#include <memory>
#include "./baseSystem.h"
#include "../components/component.h"
#include "./tickSystem.h"
#include "../utils/logger.h"
namespace onodrim::system {
	class SystemManager
	{
	public:
		SystemManager();
		~SystemManager();

		static std::shared_ptr<SystemManager> GetInstance()
		{
			static const std::shared_ptr<SystemManager> s = std::make_shared<SystemManager>();
			return s;
		}
		template <typename T>
		void AddComponentInstance(T* component)
		{
			for (auto it = m_Systems.begin(); it != m_Systems.end(); it++)
			{
				if (!(*it)->CanProcessComponent(component)) {
					continue;
				}
				(*it)->AddComponentInstance(component);
			}
		}
		void RemoveComponentInstance(Component* component);
		void AddSystem(TickSystem* system);
		void AddSystem(BaseSystem* system);
		template <typename T>
		bool HasSystem()
		{
			auto it = std::find_if(m_Systems.begin(), m_Systems.end(), [](BaseSystem* s) -> bool
			{
				return dynamic_cast<T*>(s) != nullptr;
			});
			return (it) != (m_Systems.end());
		}
		template <typename T>
		T* GetSystem()
		{
			for (auto it = m_Systems.begin(); it != m_Systems.end(); it++)
			{
				T* result = dynamic_cast<T*>((*it));
				if (result != nullptr)
				{
					return result;
				}
			}
			return NULL;
			/*auto it = std::find_if(m_Systems.begin(), m_Systems.end(), [](BaseSystem* s) -> bool
			{
				return dynamic_cast<T*>(s) != nullptr;
			});
			return (*it);*/
		}
		template <typename T>
		std::vector<BaseSystem*> GetAllSystems()
		{
			std::vector<BaseSystem*> list;
			int i = 0;
			for (auto it = m_Systems.begin(); it != m_Systems.end(); it++) {
				BaseSystem* result = dynamic_cast<T*>((*it));
				if (result != nullptr)
				{
					list.push_back(result);
				}
			}
			return list;
		}

		inline bool Tick() {
			for (auto it = m_TickSystems.begin(); it != m_TickSystems.end(); it++) {
				if (!(*it)->Tick())
				{
					return false;
				}
			}
			return true;
		}

	private:
		std::vector<BaseSystem*> m_Systems;
		std::vector<TickSystem*> m_TickSystems;
	};
}
