#include "./src/Core.h"
#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif
#include <stdio.h>
#include <stdlib.h>
/*#include "./src/Entity.h"
#include "./src/components/Transform2d.h"



#include "./src/math/Vector2.h"
#include "./src/math/Matrix3.h"*/
#include "./src/utils/Logger.h"
#include "./src/math/Random.h"
#include <time.h>
// virtual void method() override;
// bro top from alex
/*
[AxB]: om du har en virtuel metod i en basklass som du �verlagrar i en annan klass
[AxB]: om du sen �ndrar den metoden i basklassen s� s�ger kompilatorn ifr�n eftersom att den underliggande metoden inte �r samma l�ngre


*/
// using namespace std;
// using namespace onodrim;
// onodrim::random::Seed(time(NULL));

onodrim::Core* core;
#ifdef __EMSCRIPTEN__
extern "C"
{
	EMSCRIPTEN_KEEPALIVE 
	void init(int width, int height)
	{
		core = new onodrim::Core();
	}

	EMSCRIPTEN_KEEPALIVE 
	void start()
	{
		core->Start();
	}

	EMSCRIPTEN_KEEPALIVE 
	void gameloop()
	{
		core->GameLoop();
	}

	EMSCRIPTEN_KEEPALIVE 
	void destroy()
	{
		onodrim::utils::logLine("Core Destroyed");
		delete core;
	}
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