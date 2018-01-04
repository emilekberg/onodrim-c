#pragma once
#include "../../primitives/quad.h"
#include "../../shaders/program.h"
#include "../../shaders/shader.h"
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
		void End();
	protected:
		virtual void InitShaders();
		
	private:
		Quad m_quad;
		std::unique_ptr<shaders::Shader> m_Frag;
		std::unique_ptr<shaders::Shader> m_Vert;
		std::shared_ptr<shaders::Program> m_Program;
	};
}

