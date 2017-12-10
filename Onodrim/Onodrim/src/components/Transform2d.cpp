#include "./Transform2d.h"
#include "../Entity.h"
#include "../system/SystemManager.h"
namespace onodrim
{
	Transform2d::Transform2d()
	{
		m_Scale = Vector2(1, 1);
		m_IsDirty = true;
		wasDirty = true;
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
		if (m_pParent && m_pParent->wasDirty)
		{
			m_IsDirty = true;
		}
		if (m_IsDirty)
		{
			m_LocalMatrix.Identity()
				.Rotate(m_Rotation)
				.Scale(m_Scale.X, m_Scale.Y)
				.Translate(m_Position.X, m_Position.Y);
			worldMatrix = m_LocalMatrix;
			if (m_pParent) {
				worldMatrix.Multiply(m_pParent->worldMatrix);
			}
		}
		wasDirty = compensate && wasDirty ? wasDirty : m_IsDirty;
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
