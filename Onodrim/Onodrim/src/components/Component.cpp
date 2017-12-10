#include "./Component.h"
#include "../system/SystemManager.h"

namespace onodrim {
	Component::Component()
	{
		Activate();
	}


	Component::~Component()
	{
	}

	void Component::Activate()
	{
		m_IsActive = true;
	}
	void Component::Deactivate()
	{
		m_IsActive = false;
	}
	void Component::SetEntity(Entity* entity)
	{
		m_Entity = entity;
	}
}