#include "spritebatch.h"
#include "../../shaders/sprite.h"
#include "../../utils/logger.h"

namespace onodrim::system::render
{
	Spritebatch::Spritebatch()
	{
		InitShaders();
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

	void Spritebatch::Begin()
	{
		m_Program->Use();
	}

	void Spritebatch::End()
	{

	}

}
