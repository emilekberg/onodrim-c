#pragma once
#include <memory>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <string>
#include "./utils/logger.h"
#include <functional>
#include <future>
#include <chrono>
#include <memory>
using namespace onodrim::utils;
namespace FileLoader
{
	
#ifdef __EMSCRIPTEN__
	typedef std::function<void(std::string path, bool success, std::string data)> FileLoaderCallback;
	struct FileResult
	{
		std::string path;
		FileLoaderCallback callback;
	};
	void OnLoad(void* void_ptr_result, void* bufferPtr, int bufferLength)
	{
		const char* buffer = static_cast<const char*>(bufferPtr);
		std::string content(buffer, bufferLength);
		FileResult* result = static_cast<FileResult*>(void_ptr_result);
		result->callback(result->path, true, content);
		delete result;
	}

	void OnError(void* void_ptr_result)
	{
		FileResult* result = static_cast<FileResult*>(void_ptr_result);
		result->callback(result->path, false, "");
		delete result;
	}

	void ReadFile(const std::string& path, FileLoaderCallback callback)
	{
		FileResult* result = new FileResult();
		result->callback = callback;
		result->path = path;
		emscripten_async_wget_data(path.c_str(), result, &OnLoad, &OnError);
	}
#endif
}
/*
	void OnLoadPromise(void* argv, void* bufferPtr, int bufferLength)
	{
		const char* buffer = static_cast<const char*>(bufferPtr);
		std::string content(buffer, bufferLength);
		std::promise<std::string>* promise = static_cast<std::promise<std::string>*>(argv);
		promise->set_value(content);
	}
	std::string ReadFilePromise(const std::string& path)
	{
		std::promise<std::string>* readfile_promise = new std::promise<std::string>();
		std::future<std::string> future = readfile_promise->get_future();
		emscripten_async_wget_data(path.c_str(), (void*)readfile_promise, OnLoadPromise, OnError);
		std::string result = future.get();
		delete readfile_promise;
		return result;
	}

	std::string ReadFileSync(const std::string& path)
	{
		emscripten_wget(path.c_str(), path.c_str());
		FILE* img;
		img=fopen(path.c_str(), "r");
		onodrim::utils::log(path.c_str());
		return "";
		// onodrim::utils::log(img);
	}
}
*/
