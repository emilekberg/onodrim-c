#pragma once
#ifdef __EMSCRIPTEN__
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#else
#include <GL\glew.h>
#endif
#include <memory>
#include <vector>
#include "./base-batch.h"
#include "../../../data/glslProgram.h"

namespace onodrim::opengl
{
	struct IAttribute;
	class InstanceBatch : public BaseBatch
	{
	public:
		InstanceBatch(std::shared_ptr<data::GLSLProgram> program, int size) : BaseBatch(program, size)
		{
			m_IndexBuffer = NULL;
			m_InstanceArrayBuffer = NULL;
		}
		virtual ~InstanceBatch();

		virtual void CreateBuffers()
		{
			glGenBuffers(1, &m_IndexBuffer);

			int totalInstanceBufferSize = 4 * m_InstanceBufferSize * m_BatchSize;
			if(m_InstanceArrayBuffer != NULL)
			{
				delete m_InstanceArrayBuffer;
			}
			m_InstanceArrayBuffer = new float[totalInstanceBufferSize];
		}

		virtual void InitVAO()
		{
			glBindVertexArray(m_VAO);
			{
				for(auto it = m_StaticAttrib.begin(); it != m_StaticAttrib.end(); it++)
				{
					if((*it).buffer == NULL)
					{
						continue;
					}
					glBindBuffer(GL_ARRAY_BUFFER, (*it).buffer);
					// TODO: check what the 0 here is
					glBufferData(GL_ARRAY_BUFFER, 0, (*it).data, GL_STATIC_DRAW);

					glEnableVertexAttribArray((*it).index);
					glVertexAttribPointer((*it).index, (*it).size, (*it).type, (*it).normalized, (*it).stride, (*it).offset);
					glVertexAttribDivisor((*it).index, (*it).divisor);
				}

				int offset = 0;
				int totalStride = 0;
				for(auto it = m_InstanceAttrib.begin(); it != m_InstanceAttrib.end(); it++)
				{
					totalStride += (*it).stride;
				}

				glBindBuffer(GL_ARRAY_BUFFER, m_Instancebuffer);
				int i = 0;
				for(auto it = m_InstanceAttrib.begin(); it != m_InstanceAttrib.end(); it++)
				{
					const int length = (*it).length;
					for(i = 0; i < length; i++)
					{
						glEnableVertexAttribArray((*it).index + i);
					}

					for(i = 0; i < length; i++)
					{
						int currentOffset = offset + ((*it).offset * i);
						glVertexAttribPointer((*it).index + i, (*it).size, (*it).type, (*it).normalized, totalStride, currentOffset);
					}

					for(i = 0; i < length; i++)
					{
						glVertexAttribDivisor((*it).index + i, (*it).divisor);
					}
					offset += (*it).stride;
				}
				if(m_IndexBuffer != NULL)
				{
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
				}
			}
			glBindVertexArray(NULL);
			glBindBuffer(GL_ARRAY_BUFFER, m_Instancebuffer);
			// TODO: check the 0 here
			glBufferData(GL_ARRAY_BUFFER, 0, m_InstanceArrayBuffer, GL_DYNAMIC_DRAW);
		}

		virtual void Flush()
		{
			if(m_Count == 0)
			{
				return;
			}

			glBindVertexArray(m_VAO);
			{
				glBindBuffer(GL_ARRAY_BUFFER,m_Instancebuffer);
				// TODO: check this glBufferSubData
				glBufferSubData(GL_ARRAY_BUFFER, 0, 0, m_InstanceArrayBuffer);
				glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0, m_Count);
			}

			glBindVertexArray(NULL);
			glBindBuffer(GL_ARRAY_BUFFER, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
			if(m_Count == m_BatchSize && m_Count < m_MaxBatchSize)
			{
				CreateLargerBuffers();
			}
			m_Count = 0;
		}

		virtual void CreateLargerBuffers()
		{
			// TODO: implement
		}



	protected:
		// TODO: check these... these are most probably all wrong...
		GLuint m_Instancebuffer;
		// GLuint m_InstanceArrayBuffer;
		// GLuint m_InstanceBufferView;
		float* m_InstanceArrayBuffer;
		GLuint m_InstanceBufferSize;
		GLuint m_IndexBuffer;

		std::vector<IAttribute> m_StaticAttrib;
		std::vector<IAttribute> m_InstanceAttrib;
	};

}