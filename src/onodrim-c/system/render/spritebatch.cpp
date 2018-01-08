#include "spritebatch.h"
#include "../../shaders/sprite.h"
#include "../../utils/logger.h"
#include "../../math/matrix3.h"
#include "../../math/matrix4.h"
namespace onodrim::system::render
{
	Spritebatch::Spritebatch()
	{
		InitShaders();
		InitInstanceArray();
		InitVertexAttributes();
	}


	Spritebatch::~Spritebatch()
	{
	}

	void Spritebatch::InitShaders()
	{
		// TODO: read from external file or insert compiletime
		m_Program = std::make_shared<shaders::Program>();
		m_Frag = std::make_unique<shaders::Shader>(GL_FRAGMENT_SHADER);
		m_Vert = std::make_unique<shaders::Shader>(GL_VERTEX_SHADER);
		m_Program->Init();

		m_Frag->SetSource(onodrim::shaders::sprite::frag);
		m_Frag->Compile();
		m_Vert->SetSource(onodrim::shaders::sprite::vert);
		m_Vert->Compile();

		m_Program->AttachShader(*m_Vert);
		m_Program->AttachShader(*m_Frag);

		m_Program->Link();
		m_Program->Use();
		// TODO: fixed projection matrix.
		LOG_INFO("successfully initiated shaders");
	}

	void Spritebatch::InitInstanceArray()
	{
		memset(m_InstanceDataArray, 0, SIZE);
		// m_InstanceDataArray = new float[m_Size * 3 * 3 * sizeof(float)];
	}

	void Spritebatch::InitVertexAttributes()
	{
		// Hack because camera might not exist here yet. need to fix this :).
		GLint projectionLocation = glGetUniformLocation(m_Program->GetAddress(), "u_projection");
		if (projectionLocation != -1) {
			float left = 0;
			float right = 800;
			float bottom = 600;
			float top = 0;
			float near = 400;
			float far = -400;
			static Matrix4 mat4x4Ortho = 
			{
				2.0f / (right - left), 0, 0, 0,
				0, 2 / (top - bottom), 0, 0,
				0, 0, 2 / (near - far), 0,
				(left + right) / (left - right),
				(bottom + top) / (bottom - top),
				(near + far) / (near - far), 1
			};
			glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, mat4x4Ortho.GetArray());
		}

		vertLocation = glGetAttribLocation(m_Program->GetAddress(), "vertex");


		m_InstanceAttributes.push_back(InstanceAttribute<GLfloat>(glGetAttribLocation(m_Program->GetAddress(), "in_matrix"), 3, GL_FALSE, 3, 1));
		m_InstanceAttributes.push_back(InstanceAttribute<GLfloat>(glGetAttribLocation(m_Program->GetAddress(), "in_color"), 4, GL_FALSE, 1, 1));
		m_InstanceAttributes.push_back(InstanceAttribute<GLfloat>(glGetAttribLocation(m_Program->GetAddress(), "in_depth"), 1, GL_FALSE, 1, 1));
		// InstanceAttribute<GLfloat> matrixAttribute(matrixLocation, 3, false, 3, 1);

		glGenVertexArrays(1, &vao);

		glGenBuffers(3, m_GLBuffers);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_GLBuffers[BUFFER_INDEX]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(GL_UNSIGNED_BYTE), m_Quad.Indices, GL_STATIC_DRAW);

		glBindVertexArray(vao);
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_GLBuffers[BUFFER_INDEX]);


			glBindBuffer(GL_ARRAY_BUFFER, m_GLBuffers[BUFFER_VERTEX]);
			glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GL_FLOAT), m_Quad.Vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(vertLocation);
			glVertexAttribPointer(vertLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
			glVertexAttribDivisor(vertLocation, 0);

			glBindBuffer(GL_ARRAY_BUFFER, m_GLBuffers[BUFFER_INSTANCE]);
			glBufferData(GL_ARRAY_BUFFER, SIZE * ((3 * 3) + 4 + 1) * sizeof(float), m_InstanceDataArray, GL_STATIC_DRAW);

			int offset = 0;
			int currentOffset = 0;
			int totalStride = 0;
			
			for (InstanceAttribute<GLfloat>& value : m_InstanceAttributes)
			{
				totalStride += value.Stride;
			}
			for (InstanceAttribute<GLfloat>& value : m_InstanceAttributes)
			{
				for (int i = 0; i < value.Length; ++i)
				{
					currentOffset = offset + (value.Offset * i);
					glEnableVertexAttribArray(value.Index + i);
					glVertexAttribPointer(value.Index + i, value.Size, GL_FLOAT, value.Normalized, totalStride, (const void*)currentOffset);
					glVertexAttribDivisor(value.Index + i, value.Divisor);
				}
				offset += value.Stride;
			}
		}
		glBindVertexArray(NULL);
	}

	void Spritebatch::Begin()
	{
		m_Program->Use();
		m_Count = 0;
	}

	void Spritebatch::End()
	{
		Flush();
		
	}

	void Spritebatch::Render(Matrix3& matrix, Color& color, float depth)
	{
		static const int SIZE_PER_INSTANCE = 9 + 4 + 1;
		int offset = (m_Count * SIZE_PER_INSTANCE);
		memcpy(m_InstanceDataArray + offset, matrix.GetArray(), 9 * sizeof(float));
		offset += 9;
		memcpy(m_InstanceDataArray + offset, color.values, 4 * sizeof(float));
		offset += 4;
		m_InstanceDataArray[offset] = depth;
		m_Count++;
	}

	void Spritebatch::Flush()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_GLBuffers[BUFFER_INSTANCE]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_Count * ((3 * 3) + 4 + 1) * sizeof(GL_FLOAT), m_InstanceDataArray);
		glBindVertexArray(vao);
		//draw 3 vertices as triangles
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL, m_Count);
		glBindVertexArray(NULL);
		m_Count = 0;
	}

}
