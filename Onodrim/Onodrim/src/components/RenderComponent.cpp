#include "./RenderComponent.h"
#include "../Entity.h"
#include "../system/SystemManager.h"
namespace onodrim
{
	void RenderComponent::FixedUpdate(bool compensate)
	{
		m_PreviousRenderState.WasDirty = m_RenderState.WasDirty;
		m_PreviousRenderState.Matrix = m_RenderState.Matrix;
		m_PreviousRenderState.Alpha = m_RenderState.Alpha;

		UpdateTransform();
		m_RenderState.WasDirty = m_pTransform->WasDirty;
		m_RenderState.Alpha = m_Alpha;
		// m_color.a = this.alpha;
	}
}
