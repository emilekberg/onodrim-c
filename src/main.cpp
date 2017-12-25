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
		FileLoader::ReadFile("bin/shaders/sprite.web.frag", cb);
		FileLoader::ReadFile("bin/shaders/sprite.web.vert", cb);
		
		core = new onodrim::Core();
		entity = new onodrim::Entity();
		entity->AddComponent(new onodrim::Transform2d(entity));
		sprite = new onodrim::Sprite(entity);
		entity->AddComponent(sprite);
		
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
	std::string buffer =
R"({
	str: "hello",
	int: 1,
	float: 2.5
})";
	JSON j(buffer);

	onodrim::Vector<float, 3> first
	{
		0.0f, 1.0f, 0.0f
	};
	onodrim::Vector<float, 3> second
	{
		0.0f, 1.2f, 0.3f
	};

	onodrim::Vector<float, 3> third = first + second;


	first = {
		1.0f, 1.0f, 1.0f
	};



	

	core = new onodrim::Core();
	entity = new onodrim::Entity();
	entity->AddComponent(new onodrim::Transform2d(entity));
	sprite = new onodrim::Sprite(entity);
	entity->AddComponent(sprite);
	core->Start();
	return 0;
}
#endif