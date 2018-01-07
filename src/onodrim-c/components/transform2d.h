#pragma once
#include "./transform.h"
#include "../math/matrix3.h"
#include "../math/vector2.h"
#include "./fixedUpdateComponent.h"
#include <math.h>
namespace onodrim
{
	class Transform2d : public Transform, public FixedUpdateComponent
	{
	public:
		Transform2d(Entity* pEntity);
		virtual ~Transform2d();

		virtual void FixedUpdate(bool compensate);
		void SetDirty();
		void AddChildEntity(Entity* entity);

		void Translate(float dx, float dy);
		void SetPosition(float x, float y);


		bool WasDirty;
		Matrix3 WorldMatrix;

		inline float GetWorldX()
		{
			return WorldMatrix[6];
		}
		inline float GetWorldY()
		{
			return WorldMatrix[7];
		}
		inline float GetWorldScaleX()
		{
			return sqrt(pow(WorldMatrix[0], 2) + pow(WorldMatrix[1], 2));
		}
		inline float GetWorldScaleY()
		{
			return sqrt(pow(WorldMatrix[3], 2) + pow(WorldMatrix[4], 2));
		}
		inline float GetWorldRotation()
		{
			return atan2(WorldMatrix[3], WorldMatrix[0]);
		}
	protected:
		Transform2d* m_pParent;
		Vector2 m_Position;
		Vector2 m_Origo;
		Vector2 m_Scale;
		float m_Rotation;
		float m_RotationCache;
		float m_Cr;
		float m_Sr;
		bool m_IsDirty;

	private:
		Matrix3 m_LocalMatrix;
	};

}

