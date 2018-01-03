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
		static const GLfloat matrix[9] = {
			.5f,0,0,
			0,.5f,0,
			0,0,1
		};
		
		auto system = system::SystemManager::GetInstance()->GetSystem<system::render::OpenGLSystem>();
		vertLocation = glGetAttribLocation(system->GetProgram()->GetAddress(), "vertex");
		matrixLocation = glGetAttribLocation(system->GetProgram()->GetAddress(), "matrix");
		
		glGenBuffers(1, &vertex_buffer);
		glGenBuffers(1, &matrix_buffer);
		glGenBuffers(1, &index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(GL_UNSIGNED_BYTE), indices, GL_STATIC_DRAW);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
			
			
			glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
			glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GL_FLOAT), vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(vertLocation);
			glVertexAttribPointer(vertLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);

			glBindBuffer(GL_ARRAY_BUFFER, matrix_buffer);
			glBufferData(GL_ARRAY_BUFFER, 36, m_pTransform->WorldMatrix.GetArray(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(matrixLocation);
			glEnableVertexAttribArray(matrixLocation + 1);
			glEnableVertexAttribArray(matrixLocation + 2);
			glVertexAttribPointer(matrixLocation, 3, GL_FLOAT, GL_FALSE, 36, (void*)(12 * 0));
			glVertexAttribPointer(matrixLocation + 1, 3, GL_FLOAT, GL_FALSE, 36, (void*)(12 * 1));
			glVertexAttribPointer(matrixLocation + 2, 3, GL_FLOAT, GL_FALSE, 36, (void*)(12 * 2));
			glVertexAttribDivisor(matrixLocation, 1);
			glVertexAttribDivisor(matrixLocation+1, 1);
			glVertexAttribDivisor(matrixLocation+2, 1);
		}
		glBindVertexArray(NULL);
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
		m_pTransform->WorldMatrix.Translate(0.01f, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, matrix_buffer);
		glBufferData(GL_ARRAY_BUFFER, 36, m_pTransform->WorldMatrix.GetArray(), GL_STATIC_DRAW);
	}

	void Sprite::Render(float delta)
	{
		glBindVertexArray(vao);
		//draw 3 vertices as triangles
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);
		glBindVertexArray(NULL);
	}
}