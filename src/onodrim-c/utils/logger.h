#pragma once
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
namespace onodrim::utils {
	inline void log(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		vprintf(fmt, args);
		va_end(args);
		std::cout << "" << std::endl;
	}
	inline void log(const std::string& string)
	{
		std::cout << string << std::endl;
	}
}
