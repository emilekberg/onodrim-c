#pragma once
#include "../tickSystem.h"
#include "../../utils/time.h"
#include "../../components/fixedUpdateComponent.h"
namespace onodrim::system::update {
	class FixedUpdateSystem : public TickSystem
	{
	public:
		FixedUpdateSystem()
		{
			UpdateRate = 1.f / 30.f;
			CurrentUpdateTime = time::now();
			NextUpdateTime = CurrentUpdateTime + UpdateRate;
		}
		~FixedUpdateSystem()
		{

		}

		virtual inline bool CanProcessComponent(Component* component)
		{
			return dynamic_cast<FixedUpdateComponent*>(component) != nullptr;
		}
		virtual void AddComponentInstance(Component* component)
		{
			FixedUpdateComponent* casted = dynamic_cast<FixedUpdateComponent*>(component);
			m_Components.push_back(casted);
		}

		inline virtual bool Tick()
		{
			
			time::setFixedUpdateTimeStep(UpdateRate);
			int numberOfUpdates = 0;
			float now = time::now();
			while (now > NextUpdateTime)
			{
				for (auto it = m_Components.begin(); it != m_Components.end(); it++)
				{
					if (!(*it)->IsActive())
					{
						continue;
					}
					(*it)->FixedUpdate(numberOfUpdates++ > 0);
				}
				CurrentUpdateTime = NextUpdateTime;
				NextUpdateTime += UpdateRate;
				now = time::now();
			}
			return true;
		}

		float UpdateRate;
		float CurrentUpdateTime;
		float NextUpdateTime;

	private:
		std::vector<FixedUpdateComponent*> m_Components;
		
	};


}
