#pragma once
#ifndef __EMSCRIPTEN__
#include <GL/glew.h>
#else
#include <GLES3/gl3.h>
#endif
#include "../utils/logger.h"
#include "./shader.h"
namespace onodrim::shaders
{
	class Program
	{
	public:
		Program()
		{
			
		}
		~Program()
		{

		}

		inline void Init()
		{
			m_ProgramAddr = glCreateProgram();
			if (!m_ProgramAddr)
			{
				LOG_ERROR("GLSLProgram::GLSLProgram() - error when creating program");
			}
		}

		inline void AttachShader(Shader& shader)
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
				LOG_ERROR("error when linking program");
			}
		}

		inline void Use()
		{
			glUseProgram(m_ProgramAddr);
		}
		
		inline GLuint GetAddress()
		{
			return m_ProgramAddr;
		}

	protected:
		GLuint m_ProgramAddr;
	};
}
