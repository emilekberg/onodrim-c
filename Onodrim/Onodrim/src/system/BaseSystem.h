#pragma once
#include <vector>
#include "../components/Component.h"
namespace onodrim::system {
	class BaseSystem
	{
	public:
		BaseSystem() {}
		~BaseSystem() {}

		virtual bool CanProcessComponent(Component* component) = 0;
		virtual void AddComponentInstance(Component* component)
		{
			m_Components.push_back(component);
		}

		void RemoveComponentInstance(Component* component)
		{
			throw "not implemented";
		}
	protected:
		std::vector<Component*> m_Components;
	};
}
