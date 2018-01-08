#ifdef _WIN32
#include <windows.h>

#else
#define APIENTRY
#endif
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#include "./onodrim-c/core.h"
#include "./onodrim-c/entity.h"
#include "./onodrim-c/components/sprite.h"
#include "./onodrim-c/components/transform2d.h"
#include "./onodrim-c/utils/logger.h"
#include "./onodrim-c/math/random.h"
#include "./onodrim-c/fileloader.h"
#include "./onodrim-c/JSON.h"
#include "./onodrim-c/math/vector.h"
/*
#include "./src/components/Transform2d.h"



#include "./src/math/Vector2.h"
#include "./src/math/Matrix3.h"*/


// virtual void method() override;
// bro top from alex
/*
[AxB]: om du har en virtuel metod i en basklass som du �verlagrar i en annan klass
[AxB]: om du sen �ndrar den metoden i basklassen s� s�ger kompilatorn ifr�n eftersom att den underliggande metoden inte �r samma l�ngre


*/
// using namespace std;
// using namespace onodrim;
// onodrim::random::Seed(time(NULL));
using namespace onodrim::utils;
onodrim::Entity* entity;
onodrim::Sprite* sprite;
onodrim::Core* core;

class MoveComponent : public onodrim::FixedUpdateComponent
{
public:
	MoveComponent(onodrim::Entity* pEntity, int direction) : onodrim::FixedUpdateComponent(pEntity)
	{
		m_pTransform = m_pEntity->GetComponent<onodrim::Transform2d>();
		m_pSprite = m_pEntity->GetComponent<onodrim::Sprite>();
		m_Direction = direction;
		m_Depth = 10.0f;

		switch (m_Direction)
		{
		case 0:
			m_pSprite->Color.SetHex(0xff0000);
			m_pSprite->Color.SetAlpha(0.5f);
			m_pSprite->SetDepth(m_Depth);
			m_pTransform->SetPosition(100, 100);
			break;
		case 1:
			m_pSprite->Color.SetHex(0xff00ff);
			m_pSprite->SetDepth(0);
			m_pSprite->Color.SetAlpha(0.5f);
			break;
		}
	}
	virtual ~MoveComponent() {};

	virtual void FixedUpdate(bool compensate)
	{
		switch (m_Direction)
		{
		case 0:
			m_Depth -= 0.1f;
			m_pSprite->SetDepth(m_Depth);
			
			// m_pTransform->Translate(1.f, 0);
			break;
		case 1:
			// m_pTransform->Translate(0, 1.f);
			break;
		}
		LOG_DEBUG("depth: %f", m_pSprite->GetDepth());
	}

private:
	onodrim::Transform2d* m_pTransform;
	onodrim::Sprite* m_pSprite;
	int m_Direction;
	float m_Depth;
};


#ifdef __EMSCRIPTEN__
extern "C"
{
	void EMSCRIPTEN_KEEPALIVE init(int width, int height)
	{
		onodrim::Vector<float, 3> first
		{
			0.0f, 1.0f, 0.0f
		};
		onodrim::Vector<float, 3> second
		{
			0.0f, 1.2f, 0.3f
		};

		onodrim::Vector<float, 3> third = first + second;

		LOG_INFO("called from js: init(%i,%i)", width, height);
		FileLoader::FileLoaderCallback cb = [&](std::string path, bool success, std::string data)
		{
			LOG_DEBUG("ReadFile Done %i", success);
			if(success)
			{
				LOG_DEBUG(data.c_str());
			}
		};
		// FileLoader::ReadFile("bin/shaders/sprite.web.frag", cb);
		// FileLoader::ReadFile("bin/shaders/sprite.web.vert", cb);
		
		core = new onodrim::Core();
		entity = new onodrim::Entity();
		entity->AddComponent(new onodrim::Transform2d(entity));
		entity->AddComponent(new onodrim::Sprite(entity));
		entity->AddComponent(new MoveComponent(entity, 0));

		entity = new onodrim::Entity();
		entity->AddComponent(new onodrim::Transform2d(entity));
		entity->AddComponent(new onodrim::Sprite(entity));
		entity->AddComponent(new MoveComponent(entity, 1));
	}

	void EMSCRIPTEN_KEEPALIVE gameloop()
	{
		core->GameLoop();
	}

	void EMSCRIPTEN_KEEPALIVE start()
	{
		core->Start();
		// check an see if this can be moved into gameloop
		emscripten_set_main_loop(gameloop, 0, 0);
	}

	void EMSCRIPTEN_KEEPALIVE destroy()
	{
		LOG_INFO("called from js: destroy()");
		delete core;
	}
}
#else
int main()
{
	core = new onodrim::Core();
	entity = new onodrim::Entity();
	entity->AddComponent(new onodrim::Transform2d(entity));
	entity->AddComponent(new onodrim::Sprite(entity));
	entity->AddComponent(new MoveComponent(entity, 0));

	entity = new onodrim::Entity();
	entity->AddComponent(new onodrim::Transform2d(entity));
	entity->AddComponent(new onodrim::Sprite(entity));
	entity->AddComponent(new MoveComponent(entity, 1));

	core->Start();
	return 0;
}
#endif