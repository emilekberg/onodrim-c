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

onodrim::Entity* entity;
onodrim::Sprite* sprite;
onodrim::Core* core;
#ifdef __EMSCRIPTEN__




extern "C"
{
	void EMSCRIPTEN_KEEPALIVE init(int width, int height)
	{
		FileLoader::ReadFile();
		
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
		onodrim::utils::log("Core Destroyed");
		delete core;
	}
}
#else
int main()
{
	core = new onodrim::Core();
	entity = new onodrim::Entity();
	entity->AddComponent(new onodrim::Transform2d(entity));
	sprite = new onodrim::Sprite(entity);
	entity->AddComponent(sprite);
	core->Start();
	return 0;
}
#endif

/*
int main() 
{
	onodrim::utils::logLine("Hello World!");
	
	onodrim::random::Seed(time(NULL));
	onodrim::Vector2 vector;
	onodrim::Matrix3 mat;

	mat.Identity().Translate(1, 0);
	onodrim::utils::logLine("some value");

	onodrim::Core* core = new onodrim::Core();
	

	Entity* parent = new Entity();
	Entity* child = new Entity();

	
	Transform2d* parentTransform = new Transform2d();
	Transform2d* childTransform = new Transform2d();
	utils::logLine("create Transform for parent");
	parent->AddComponent(parentTransform);
	utils::logLine("create Transform for child");
	child->AddComponent(childTransform);
	utils::logLine("create empty component for child");
	child->AddComponent(new Component());

	Component* test = dynamic_cast<Component*>(childTransform);
	Entity* test2 = dynamic_cast<Entity*>(childTransform);
	parentTransform->AddChildEntity(child);


	// core->Start();
	return 0;
}

*/