#pragma once
#include <memory>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <string>
#include "./utils/logger.h"
#include <functional>
class FileLoader
{
public:
	FileLoader();
	~FileLoader();

#ifdef __EMSCRIPTEN__
	static void OnLoad(void* argv, void* bufferPtr, int bufferLength)
	{
		auto arr = static_cast<std::string*>(argv);
		
		const char* buffer = static_cast<const char*>(bufferPtr);
		std::string content(buffer, bufferLength);
		onodrim::utils::log("OnLoad %s", (arr));
		delete arr;
		onodrim::utils::log("OnLoad %s %i", content.c_str(), bufferLength);
	}

	static void OnError(void* argv)
	{
		const char* arr = static_cast<const char*>(argv);
		onodrim::utils::log("OnError %s", argv);
	}

	static void ReadFile()
	{
		std::string* str = new std::string("test");
		const char* path = "bin/sprite.frag";
		std::string argv[1] = { "Something" };
		onodrim::utils::log("%i", sizeof(argv));
		emscripten_async_wget_data(path, str, &OnLoad, &OnError);
	}
#endif
protected:
};

