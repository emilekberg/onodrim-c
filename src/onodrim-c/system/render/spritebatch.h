#pragma once
#include "../../primitives/quad.h"
#include "../../shaders/program.h"
#include "../../shaders/shader.h"
#include <array>
#include "../../math/matrix3.h"
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
		void Render(Matrix3& matrix);
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

		float m_InstanceDataArray[SIZE * 3 * 3 * sizeof(float)];

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

