#pragma once
#include "./TickSystem.h"
#include "../components/UpdateComponent.h"
#include "../utils/Time.h"
namespace onodrim::system {
	class UpdateSystem : public TickSystem
	{
	public:
		UpdateSystem(){}
		~UpdateSystem(){}

		virtual inline bool CanProcessComponent(Component* component)
		{
			return dynamic_cast<UpdateComponent*>(component) != nullptr;
		}

		inline virtual void Tick()
		{
			time::update();
			for (auto it = m_Components.begin(); it != m_Components.end(); it++)
			{
				(*it)->Update();
			}
		}

	private:
		std::vector<UpdateComponent*> m_Components;
	};


}
