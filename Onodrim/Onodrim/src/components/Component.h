#pragma once
namespace onodrim {
	class Entity;
	class Component
	{
	public:
		Component();
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
			return m_Entity;
		}

	protected:
		bool m_IsActive;
		Entity* m_Entity;

	};
}