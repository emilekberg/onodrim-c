#pragma once
namespace onodrim {
	class Entity;
	class Component
	{
	public:
		Component(Entity* pEntity);
		virtual ~Component();

		inline bool IsActive()
		{
			return m_IsActive;
		}

		void Activate();
		void Deactivate();
		void SetEntity(Entity* entity);
		inline Entity* GetEntity()
		{
			return m_pEntity;
		}

	protected:
		bool m_IsActive;
		Entity* m_pEntity;

	};
}