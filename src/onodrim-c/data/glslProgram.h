#pragma once
#ifndef __EMSCRIPTEN__
#include <GL/glew.h>
#else
#include <GLES3/gl3.h>
#endif
#include "../utils/logger.h"
#include "./glslShader.h"
namespace onodrim::data
{
	class GLSLProgram
	{
	public:
		GLSLProgram()
		{
			
		}
		~GLSLProgram()
		{

		}

		inline void Init()
		{
			m_ProgramAddr = glCreateProgram();
			if (!m_ProgramAddr)
			{
				utils::log("GLSLProgram::GLSLProgram() - error when creating program");
			}
		}

		inline void AttachShader(GLSLShader& shader)
		{
			glAttachShader(m_ProgramAddr, shader.GetShaderAddr());
		}
	
		inline void Link()
		{
			glLinkProgram(m_ProgramAddr);

			GLint success = 0;
			glGetProgramiv(m_ProgramAddr, GL_LINK_STATUS, &success);
			if (!success)
			{
				utils::log("error when linking program");
			}
		}

		inline void Use()
		{
			glUseProgram(m_ProgramAddr);
		}

	protected:
		GLuint m_ProgramAddr;
	};
}
