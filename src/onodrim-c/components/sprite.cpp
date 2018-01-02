#include "./sprite.h"
#include "../utils/logger.h"
#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#else
#include <GL\glew.h>
#endif
#include "../system/render/openGLSystem.h"
#include "../system/systemManager.h"
namespace onodrim
{
	Sprite::Sprite(Entity* pEntity) : RenderComponent(pEntity)
	{
		X = 0;
		Y = 0;

		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GL_FLOAT), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, NULL);

		glGenBuffers(1, &index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2*3*sizeof(GL_UNSIGNED_BYTE), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

		auto system = system::SystemManager::GetInstance()->GetSystem<system::render::OpenGLSystem>();
		vertLocation = glGetAttribLocation(system->GetProgram()->GetAddress(), "vertex");
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
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

		glVertexAttribPointer(vertLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(vertLocation);

		//draw 3 vertices as triangles
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
	}
}