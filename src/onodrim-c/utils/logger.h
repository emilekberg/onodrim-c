#pragma once
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>

static const unsigned char LOG_LEVEL_INFO = 0;
static const unsigned char LOG_LEVEL_DEBUG = 1;
static const unsigned char LOG_LEVEL_ERROR = 2;
static const unsigned char LOG_LEVEL_FATAL = 3;
static unsigned int LOG_LINE = 0;
static const char* LOG_LEVEL_STRINGS[] = {
	"INFO",
	"DEBUG",
	"ERROR",
	"FATAL"
};

namespace onodrim::utils
{
	static inline void log(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}
	static inline void log(std::string line)
	{
		std::cout << line.c_str() << std::endl;
	}
	static inline void log(int level, int file_line, const char* file, const char* function, const char* format, ...)
	{
		printf("%s:\t", LOG_LEVEL_STRINGS[level]);
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
		printf("\t\t%s:%i:%s\r\n", file, file_line, function);
	}
}


#define LOG_GENERAL(level, format, ...) onodrim::utils::log(level, __LINE__, __FILE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) LOG_GENERAL(LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) LOG_GENERAL(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) LOG_GENERAL(LOG_LEVEL_ERROR, format, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) LOG_GENERAL(LOG_LEVEL_FATAL, format, ##__VA_ARGS__)
