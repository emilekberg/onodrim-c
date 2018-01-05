#include "./renderComponent.h"
#include "../entity.h"
#include "../system/systemManager.h"
#include "../math/math.h"
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
		Color.SetAlpha(m_Alpha);
	}

	void RenderComponent::InterpolateRenderMatrix(float delta)
	{
		if (!m_RenderState.WasDirty && !m_PreviousRenderState.WasDirty) {
			return;
		}
		math::matrixLerp(m_RenderMatrix, m_PreviousRenderState.Matrix, m_RenderState.Matrix, delta);
	}
}
