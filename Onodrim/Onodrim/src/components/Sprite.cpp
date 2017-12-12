#include "./Sprite.h"
#include "../utils/Logger.h"
namespace onodrim
{
	Sprite::Sprite(Entity* pEntity) : RenderComponent(pEntity)
	{
		X = 0;
		Y = 0;
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::UpdateTransform()
	{
		if(m_pTransform->WasDirty)
		{
			m_RenderState.Matrix
				.Identity()
				.Scale(1, 1)
				.Multiply(m_pTransform->WorldMatrix)
				.Translate(X, Y);
		}
	}

	void Sprite::Render(float delta)
	{

	}
}