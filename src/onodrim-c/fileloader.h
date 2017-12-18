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
		onodrim::utils::log("Finished loading %s", (arr));
		const char* buffer = static_cast<const char*>(bufferPtr);
		std::string content(buffer, bufferLength);
		
		delete arr;
		onodrim::utils::log("OnLoad %s %i", content.c_str(), bufferLength);
	}

	static void OnError(void* argv)
	{
		const char* arr = static_cast<const char*>(argv);
		onodrim::utils::log("OnError %s", argv);
	}

	static void ReadFile(const std::string& path)
	{
		std::string* identifier = new std::string("test");
		// const char* path = "bin/sprite.frag";
		onodrim::utils::log("ReadFile %s %s", path.c_str(), identifier->c_str());
		emscripten_async_wget_data(path.c_str(), identifier, &OnLoad, &OnError);
	}
#endif
protected:


};

