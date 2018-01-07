#pragma once
#include "./fixedUpdateComponent.h"
#include "../math/matrix3.h"
#include "../math/vector.h"

namespace onodrim
{
	class Entity;
	class Transform2d;
	class Camera2D : public FixedUpdateComponent
	{
	public:
		Camera2D(Entity* pEntity);
		~Camera2D();

		void FixedUpdate(bool compensate);
		void SetViewPort(int width, int height);
		void InterpolateMatrix(float delta);
		void UpdateProjectionMatrix();
		void UpdateViewMatrix();

		Matrix3 Matrix;
	protected:
		
		Matrix3 m_CurrentMatrix;
		Matrix3 m_PreviousMatrix;
		Matrix3 m_Projection;
		Matrix3 m_View;
		Vector<float, 2> m_Viewport;
		Transform2d* m_pTransform;
		bool m_IsDirty;

	};
}