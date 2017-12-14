#include "./component.h"
#include "../system/systemManager.h"

namespace onodrim {
	Component::Component(Entity* pEntity)
	{
		SetEntity(pEntity);
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
	void Component::SetEntity(Entity* pEntity)
	{
		m_pEntity = pEntity;
	}
}