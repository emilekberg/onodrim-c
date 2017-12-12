#pragma once
#include "../math/Vector2.h"
#include "./RenderComponent.h"
namespace onodrim
{
	class Sprite : public RenderComponent
	{
	public:
		Sprite(Entity* pEntity);
		~Sprite();

		float X;
		float Y;

		void UpdateTransform();
		void Render(float delta);

	protected:
		float m_Width;
		float m_Height;

		Vector2 m_Offset;
	};
}
