#pragma once
#include "./Component.h"
namespace onodrim {
	class RenderComponent : public Component
	{
	public:
		RenderComponent() {};
		virtual ~RenderComponent() {};

		virtual void Render(float renderDelta) = 0;

		inline bool DoesRequireDepthSort()
		{
			return m_ZChanged;
		}
		inline void SetRequireDepthSort(bool resort)
		{
			m_ZChanged = resort;
		}
		inline virtual float GetDepth()
		{
			return m_Depth;
		}

	protected:
		bool m_ZChanged;
		float m_Depth;
	};


}
