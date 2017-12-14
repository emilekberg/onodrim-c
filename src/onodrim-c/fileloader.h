#pragma once
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
		const char* arr = static_cast<const char*>(argv);
		const char* buffer = static_cast<const char*>(bufferPtr);
		std::string content(buffer, bufferLength);
		onodrim::utils::log("OnLoad %s", (&arr[0]));
		onodrim::utils::log("OnLoad %s %i", content.c_str(), bufferLength);
	}

	static void OnError(void* argv)
	{
		const char* arr = static_cast<const char*>(argv);
		onodrim::utils::log("OnError %s", argv);
	}

	void ReadFile()
	{
		const char* file = "bin/sprite";
		const char* path = "bin/sprite.frag";
		const char *argv[1] = { "Something" };
		onodrim::utils::log("ReadFile %s", argv[0]);
		emscripten_async_wget_data(path, &argv, OnLoad, OnError);
	}
#endif
protected:

};

