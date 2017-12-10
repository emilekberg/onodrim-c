#include "./Entity.h"
#include "./components/Component.h"
#include "./system/SystemManager.h"
namespace onodrim {
	unsigned long Entity::NUM_ENTITIES = 0;
	Entity::Entity()
	{
		m_Components = std::vector<Component*>();
		m_AddedToWorld = false;
		m_ID = Entity::NUM_ENTITIES++;
		m_Name = "entity" + std::to_string(m_ID);
	}


	Entity::~Entity()
	{

	}

	void Entity::AddedToWorld()
	{
		m_AddedToWorld = true;
	}
	void Entity::RemovedFromWorld()
	{
		m_AddedToWorld = false;
	}
	void Entity::AddComponent(Component* component)
	{
		component->SetEntity(this);
		m_Components.push_back(component);
		system::SystemManager::GetInstance()->AddComponentInstance(component);
	}
	const std::vector<Component*>& Entity::GetAllComponents()
	{
		return m_Components;
	}
	void Entity::RemoveComponent()
	{
		throw "not yet implmented";
		// system::SystemManager::GetInstance()->RemoveComponentInstance();
	}
}