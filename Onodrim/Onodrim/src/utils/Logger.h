#pragma once
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
namespace onodrim::utils {
	inline void log(const char *fmt, ...)
	{
		char buffer[4096];
		va_list args;
		va_start(args, fmt);
		int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);
		std::cout << buffer;
		va_end(args);
	}
	inline void log(const std::string& string)
	{
		std::cout << string << std::endl;
	}
}
