#pragma once
#include <string>
#ifndef __EMSCRIPTEN__
#include <GL/glew.h>
#else
#include <GLES3/gl3.h>
#endif
#include "../utils/logger.h"
namespace onodrim::shaders
{
	class Shader
	{
	public:
		Shader(GLuint shaderType)
		{
			m_ShaderAddr = glCreateShader(shaderType);
			m_ShaderType = shaderType;
			m_Path = "";
		}
		~Shader()
		{

		}

		void Load(const std::string& path)
		{
			m_Path = path;
			// load source;
		}

		void SetSource(const std::string& source)
		{
			LOG_INFO("GLSLShader::SetSource");
			m_Source = source;
			const GLchar* src = ((const GLchar*)m_Source.c_str());
			glShaderSource(m_ShaderAddr, 1, &src, 0);
		}

		bool Compile()
		{
			glCompileShader(m_ShaderAddr);
			GLint compileSuccessful = 0;
			glGetShaderiv(m_ShaderAddr, GL_COMPILE_STATUS, &compileSuccessful);
			if (compileSuccessful == GL_FALSE)
			{
				LOG_ERROR("Error when compiling shader, path: %s", m_Path.c_str());
				GLint maxLength = 0;
				glGetShaderiv(m_ShaderAddr, GL_INFO_LOG_LENGTH, &maxLength);

				GLchar* errorLog = new GLchar[maxLength + 1];
				glGetShaderInfoLog(m_ShaderAddr, maxLength, &maxLength, errorLog);

				LOG_ERROR("%s", errorLog);
				glDeleteShader(m_ShaderAddr);
				m_ShaderAddr = NULL;
				return false;
			}
			return true;
		}

		GLuint GetShaderAddr()
		{
			return m_ShaderAddr;
		}

	protected:
		std::string m_Path;
		GLuint m_ShaderType;
		GLuint m_ShaderAddr;
		std::string m_Source;
	};
}
