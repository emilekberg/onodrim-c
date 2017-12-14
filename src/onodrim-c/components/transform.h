#pragma once
#include <vector>

namespace onodrim
{
	class Transform
	{
	public:
		Transform();
		virtual ~Transform();

		Transform* GetParent();
		bool HasParent();
		void AddChild(Transform* child);
		void RemoveChild(Transform* child);
		bool IsChild(Transform* child);
		

	protected:
		std::vector<Transform*> m_Children;
		Transform* m_pParent;
	};
}
