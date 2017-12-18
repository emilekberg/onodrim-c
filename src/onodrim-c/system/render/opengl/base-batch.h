#pragma once
#ifdef __EMSCRIPTEN__
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#else
#include <GL\glew.h>
#endif
#include <memory>
#include "../../../data/glslProgram.h"

namespace onodrim::opengl
{
	struct IAttribute
	{
		float* data = NULL;
		GLuint buffer = NULL;
		int index;
		int size;
		int type;
		bool normalized;
		int stride;
		int offset;
		int divisor;
		int length;
	};
	class BaseBatch
	{
	public:
		BaseBatch(std::shared_ptr<data::GLSLProgram> program, int size)
		{
			m_Program = program;
			m_BatchSize = size;
			m_MaxBatchSize = size * 100;
			m_Count = 0;
		}
		virtual ~BaseBatch();

	protected:
		void Init()
		{
			CreateVAO();
			CreateBuffers();
			InitVAO();
		}
		void CreateVAO()
		{
			glGenVertexArrays (1, &m_VAO);
		}
		virtual void InitVAO() = 0;
		

		virtual void CreateBuffers() = 0;
		virtual void CreateLargerBuffers() = 0;
		void DoFlush()
		{
			Flush();
		}
		virtual void Flush() = 0;
		
		std::shared_ptr<data::GLSLProgram> m_Program;
		GLuint m_VAO;
		int m_BatchSize;
		int m_MaxBatchSize;
		int m_Count;
	};


}
