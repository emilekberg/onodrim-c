#pragma once
#include <string>
#include <iostream>
namespace onodrim::utils {
	inline void log(const std::string& string)
	{
		std::cout << string;
	}

	inline void endLine()
	{
		std::cout << std::endl;
	}

	inline void logLine(const std::string& string)
	{
		std::cout << string << std::endl;
	}

}
