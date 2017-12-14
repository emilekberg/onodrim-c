#pragma once
#include "./transform.h"
#include "../math/matrix3.h"
#include "../math/vector2.h"
#include "./fixedUpdateComponent.h"
namespace onodrim
{
	class Transform2d : public Transform, public FixedUpdateComponent
	{
	public:
		Transform2d(Entity* pEntity);
		virtual ~Transform2d();

		virtual void FixedUpdate(bool compensate);
		void SetDirty();
		void AddChildEntity(Entity* entity);

		bool WasDirty;
		Matrix3 WorldMatrix;
	protected:
		Transform2d* m_pParent;
		Vector2 m_Position;
		Vector2 m_Origo;
		Vector2 m_Scale;
		float m_Rotation;
		float m_RotationCache;
		float m_Cr;
		float m_Sr;
		bool m_IsDirty;

	private:
		Matrix3 m_LocalMatrix;
	};

}

