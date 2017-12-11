#pragma once
#include "../TickSystem.h"
#include "../../utils/Time.h"
#include "../../components/FixedUpdateComponent.h"
namespace onodrim::system::update {
	class FixedUpdateSystem : public TickSystem
	{
	public:
		FixedUpdateSystem()
		{
			m_UpdateRate = 1.f / 30.f;
			m_CurrentUpdateTime = time::now();
			m_NextUpdateTime = m_CurrentUpdateTime + m_UpdateRate;
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

		inline virtual void Tick()
		{
			
			time::setFixedUpdateTimeStep(m_UpdateRate);
			int numberOfUpdates = 0;
			float now = time::now();
			while (now > m_NextUpdateTime)
			{
				for (auto it = m_Components.begin(); it != m_Components.end(); it++)
				{
					if (!(*it)->IsActive())
					{
						continue;
					}
					(*it)->FixedUpdate(numberOfUpdates++ > 0);
				}
				m_CurrentUpdateTime = m_NextUpdateTime;
				m_NextUpdateTime += m_UpdateRate;
				now = time::now();
			}
			
		}

	private:
		std::vector<FixedUpdateComponent*> m_Components;
		float m_UpdateRate;
		float m_CurrentUpdateTime;
		float m_NextUpdateTime;
	};


}
