#pragma once
#include "../tickSystem.h"
#include "../../components/updateComponent.h"
#include "../../utils/time.h"
namespace onodrim::system::update {
	class UpdateSystem : public TickSystem
	{
	public:
		UpdateSystem(){}
		~UpdateSystem(){}

		virtual inline bool CanProcessComponent(Component* component)
		{
			return dynamic_cast<UpdateComponent*>(component) != nullptr;
		}

		inline virtual bool Tick()
		{
			time::update();
			for (auto it = m_Components.begin(); it != m_Components.end(); it++)
			{
				(*it)->Update();
			}
			return true;
		}

	private:
		std::vector<UpdateComponent*> m_Components;
	};


}
