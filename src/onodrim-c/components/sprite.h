#pragma once
#include "../math/vector2.h"
#include "./renderComponent.h"
#include <array>
#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#else
#include <GL\glew.h>
#endif
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
		const GLfloat vertices[8] = {
			-1, -1,
			-1, 1,
			1, 1,
			1, -1
		};
		const GLubyte indices[6] {
			0, 1, 2,
			0, 2, 3
		};

		GLuint vertex_buffer = NULL;
		GLuint index_buffer = NULL;
		GLint vertLocation = NULL;



		float m_Width;
		float m_Height;

		Vector2 m_Offset;
	};
}
