#include "spritebatch.h"
#include "../../shaders/sprite.h"
#include "../../utils/logger.h"
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
		vertLocation = glGetAttribLocation(m_Program->GetAddress(), "vertex");
		matrixLocation = glGetAttribLocation(m_Program->GetAddress(), "matrix");


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
			glBufferData(GL_ARRAY_BUFFER, SIZE * 3 * 3 * sizeof(float), m_InstanceDataArray, GL_STATIC_DRAW);

			glEnableVertexAttribArray(matrixLocation);
			glEnableVertexAttribArray(matrixLocation + 1);
			glEnableVertexAttribArray(matrixLocation + 2);
			glVertexAttribPointer(matrixLocation, 3, GL_FLOAT, GL_FALSE, 3 * 3 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT) * 0));
			glVertexAttribPointer(matrixLocation + 1, 3, GL_FLOAT, GL_FALSE, 3 * 3 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT) * 1));
			glVertexAttribPointer(matrixLocation + 2, 3, GL_FLOAT, GL_FALSE, 3 * 3 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT) * 2));
			glVertexAttribDivisor(matrixLocation, 1);
			glVertexAttribDivisor(matrixLocation + 1, 1);
			glVertexAttribDivisor(matrixLocation + 2, 1);
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

	void Spritebatch::Render(Matrix3& matrix)
	{
		memcpy(m_InstanceDataArray + (m_Count * 9), matrix.GetArray(), 9 * sizeof(float));
		m_Count++;
	}

	void Spritebatch::Flush()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_GLBuffers[BUFFER_INSTANCE]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_Count * 3 * 3 * sizeof(GL_FLOAT), m_InstanceDataArray);
		glBindVertexArray(vao);
		//draw 3 vertices as triangles
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL, m_Count);
		glBindVertexArray(NULL);
		m_Count = 0;
	}

}
