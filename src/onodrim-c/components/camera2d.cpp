#include "./camera2d.h"
#include "../entity.h"
#include "./transform2d.h"
#include "../utils/logger.h"
// #include "../math/math.h"

// https://stackoverflow.com/questions/31839119/projection-and-orthographic-matrices-for-opengl 
// apply this here in future. 2D camera should probably use Matrix4.
namespace onodrim
{
	Camera2D::Camera2D(Entity* pEntity) : FixedUpdateComponent(pEntity)
	{
		m_pTransform = pEntity->GetComponent<Transform2d>();
		if (m_pTransform == NULL)
		{
			LOG_ERROR("No transform component found");
		}

		m_IsDirty = true;
	}


	Camera2D::~Camera2D()
	{
	}

	void Camera2D::FixedUpdate(bool compensate)
	{
		m_PreviousMatrix = m_CurrentMatrix;
		if (m_IsDirty)
		{
			UpdateViewMatrix();
			m_CurrentMatrix = m_View;
			m_CurrentMatrix.Translate(m_Viewport[0] * 0.5f, m_Viewport[1] * 0.5f);

			m_IsDirty = false;
		}
	}

	void Camera2D::SetViewPort(int width, int height)
	{
		m_IsDirty = true;
		m_Viewport[0] = static_cast<float>(width);
		m_Viewport[1] = static_cast<float>(height);
		UpdateProjectionMatrix();
		UpdateViewMatrix();
	}

	void Camera2D::InterpolateMatrix(float delta)
	{
		// math::matrixLerp(Matrix, m_PreviousMatrix, m_CurrentMatrix, delta);
		Matrix *= m_Projection;
	}

	void Camera2D::UpdateProjectionMatrix()
	{
		m_Projection.Identity()
			.Scale(1.0f / (float)m_Viewport[0], 1.0f / (float)m_Viewport[1])
			.Scale(2, 2)
			.Translate(-1, -1)
			.Scale(1, -1);
	}

	void Camera2D::UpdateViewMatrix()
	{
		m_View.Identity()
			.Translate(-m_pTransform->GetWorldX(), -m_pTransform->GetWorldY())
			.Scale(m_pTransform->GetWorldScaleX(), m_pTransform->GetWorldScaleY())
			.Rotate(m_pTransform->GetWorldRotation());
	}

}