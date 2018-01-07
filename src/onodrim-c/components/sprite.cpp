#include "./sprite.h"
#include "../utils/logger.h"
#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#else
#include <GL\glew.h>
#endif
#include "../system/render/render-system.h"
#include "../system/systemManager.h"
#include "../primitives/quad.h"
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
				.Scale(100, 100)
				.Multiply(m_pTransform->WorldMatrix)
				.Translate(X, Y);
		}
	}

	void Sprite::Render(float delta)
	{
		auto spritebatch = system::SystemManager::GetInstance()->GetSystem<system::render::RenderSystem>()->GetSpriteBatch();
		InterpolateRenderMatrix(delta);
		spritebatch->Render(m_RenderMatrix, Color);
	}
}