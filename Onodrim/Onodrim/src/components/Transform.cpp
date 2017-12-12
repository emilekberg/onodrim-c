#include "./Transform.h"

namespace onodrim 
{
	Transform::Transform()
	{
	}


	Transform::~Transform()
	{
	}

	Transform* Transform::GetParent()
	{
		return m_pParent;
	}
	bool Transform::HasParent()
	{
		return m_pParent != NULL;
	}
	void Transform::AddChild(Transform* child)
	{
		if (IsChild(child)) {
			return;
		}
		m_Children.push_back(child);
		if (child->HasParent())
		{
			child->m_pParent->RemoveChild(child);
		}
		child->m_pParent = this;
		
	}
	void Transform::RemoveChild(Transform* child)
	{
		throw "Not implmented";
	}
	bool Transform::IsChild(Transform* child)
	{
		auto it = std::find(m_Children.begin(), m_Children.end(), child);
		return it != m_Children.end();
	}


}

