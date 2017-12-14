#include "./sprite.h"
#include "../utils/logger.h"
#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#else
#include <GL\glew.h>
#endif
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
		//draw 3 vertices as triangles
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}