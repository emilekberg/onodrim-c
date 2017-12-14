#pragma once
#include <vector>
#include <algorithm>
#include <string>

namespace onodrim {
	class Component;
	class Entity
	{
	public:
		Entity();
		~Entity();

		static unsigned long NUM_ENTITIES;

		void AddedToWorld();
		void RemovedFromWorld();
		void AddComponent(Component* component);
		void RemoveComponent();
		const std::vector<Component*>& GetAllComponents();

		template <typename T>
		bool HasComponent()
		{
			auto it = std::find_if(m_Components.begin(), m_Components.end(), [](Component* c) -> bool
			{
				return dynamic_cast<T*>(c) != nullptr;
			});
			return (it) != (m_Components.end());
		}
		template <typename T>
		T* GetComponent()
		{
			for (auto it = m_Components.begin(); it != m_Components.end(); it++)
			{
				T* result = dynamic_cast<T*>((*it));
				if (result != nullptr)
				{
					return result;
				}
			}
			return NULL;
		}
		template <typename T>
		std::vector<T*> GetComponents()
		{
			std::vector<Component*> list;
			int i = 0;
			for (auto it = m_Components.begin(); it != m_Components.end(); it++) {
				Component* result = dynamic_cast<T*>((*it));
				if (result != nullptr)
				{
					list.push_back(result);
				}
			}
			return list;
		}
	
	private:
		bool m_AddedToWorld;
		std::vector<Component*> m_Components;
		int m_ID;
		std::string m_Name;
	};
};