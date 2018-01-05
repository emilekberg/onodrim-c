#pragma once
#include "../../primitives/quad.h"
#include "../../shaders/program.h"
#include "../../shaders/shader.h"
#include <array>
#include <vector>
#include "../../math/matrix3.h"
#include "../../data/color.h"

template <typename T>
struct InstanceAttribute
{
	int Type;
	GLuint Index;
	int Size;
	bool Normalized;
	int Stride;
	int Offset;
	int Length;
	int Divisor;

	InstanceAttribute(GLuint index, int size, bool normalized, int length, int divisor)
	{
		if (std::is_same<T, GLfloat>::value)
		{
			Type = GL_FLOAT;
		}
		else if (std::is_same<T, GLuint>::value)
		{
			Type = GL_UNSIGNED_INT;
		}
		Index = index;
		Size = size;
		Normalized = normalized;
		Length = length;
		Divisor = divisor;

		Stride = Size * sizeof(T) * Length;
		Offset = Size * sizeof(T);
	}
};

namespace onodrim::system::render
{
	class Spritebatch
	{
	public:
		Spritebatch();
		~Spritebatch();

		inline std::shared_ptr<shaders::Program> GetProgram()
		{
			return m_Program;
		}

		void Begin();
		void Render(Matrix3& matrix, Color& color);
		void End();
		void Flush();
	protected:
		virtual void InitShaders();
		virtual void InitVertexAttributes();
		virtual void InitInstanceArray();
		
	private:
		const static int BUFFER_VERTEX = 0;
		const static int BUFFER_INDEX = 1;
		const static int BUFFER_INSTANCE = 2;
		const static int SIZE = 2000;

		float m_InstanceDataArray[SIZE * ((3 * 3) + 4) * sizeof(float)];

		std::vector<InstanceAttribute<GLfloat>> m_InstanceAttributes;
		GLuint vao;

		GLuint m_GLBuffers[3];

		GLint vertLocation = NULL;
		GLint matrixLocation = NULL;

		int m_Count;
		Quad m_Quad;
		std::unique_ptr<shaders::Shader> m_Frag;
		std::unique_ptr<shaders::Shader> m_Vert;
		std::shared_ptr<shaders::Program> m_Program;
	};
}

