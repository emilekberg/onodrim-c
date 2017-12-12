#include "./Transform2d.h"
#include "../Entity.h"
#include "../system/SystemManager.h"
namespace onodrim
{
	Transform2d::Transform2d(Entity* pEntity) : FixedUpdateComponent(pEntity)
	{
		m_Scale = Vector2(1, 1);
		m_IsDirty = true;
		WasDirty = true;
		m_Rotation = 0;
		m_RotationCache = 0;
		m_Sr = 0;
		m_Cr = 0;
	}


	Transform2d::~Transform2d()
	{
	}

	void Transform2d::FixedUpdate(bool compensate)
	{
		if (m_pParent && m_pParent->WasDirty)
		{
			m_IsDirty = true;
		}
		if (m_IsDirty)
		{
			m_LocalMatrix.Identity()
				.Rotate(m_Rotation)
				.Scale(m_Scale.X, m_Scale.Y)
				.Translate(m_Position.X, m_Position.Y);
			WorldMatrix = m_LocalMatrix;
			if (m_pParent) {
				WorldMatrix.Multiply(m_pParent->WorldMatrix);
			}
		}
		WasDirty = compensate && WasDirty ? WasDirty : m_IsDirty;
		m_IsDirty = false;
	}

	void Transform2d::SetDirty()
	{
		m_IsDirty = true;
	}
	void Transform2d::AddChildEntity(Entity* entity)
	{
		Transform2d* transform = entity->GetComponent<Transform2d>();
		if (!transform)
		{
			return;
		}
		AddChild(transform);
	}
}
