#pragma once
#include "./component.h"
#include "./fixedUpdateComponent.h"
#include "./transform2d.h"
#include "../math/matrix3.h"
#include "../data/renderState.h"
#include "../entity.h"
namespace onodrim {
	class RenderComponent : public FixedUpdateComponent
	{
	public:
		RenderComponent(Entity* pEntity) : FixedUpdateComponent(pEntity)
		{
			m_pTransform = m_pEntity->GetComponent<Transform2d>();
		};
		virtual ~RenderComponent() {};

		void destroy() {
			/*
			const webglSystem = SystemManager.getSystem(WebGLSystem);
			if (webglSystem) {
				webglSystem.removeComponentInstance(this);
			}
			*/
		}

		virtual void FixedUpdate(bool compensate);

		void Reset() {
			UpdateTransform();
			m_RenderState.Alpha = m_Alpha;
			m_PreviousRenderState.Matrix = m_RenderState.Matrix;
			m_PreviousRenderState.Alpha = m_RenderState.Alpha;
			m_PreviousRenderState.WasDirty = true;
			m_RenderState.WasDirty = true;
		}

		virtual void UpdateTransform()
		{
			m_RenderState.Matrix = m_pTransform->WorldMatrix;
		}
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

		inline virtual bool IsVisible()
		{
			return m_Visible && m_Alpha > 0;
		}

		

	protected:
		bool m_ZChanged;
		bool m_Visible;
		float m_Alpha;
		float m_Depth;
		data::RenderState m_RenderState;
		data::RenderState m_PreviousRenderState;
		Transform2d* m_pTransform;
	};


}
