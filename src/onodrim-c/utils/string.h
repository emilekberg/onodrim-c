#pragma once
#include <vector>
#include <string>
namespace onodrim::utils {
	std::vector<std::string> split(std::string& str, char split)
	{
		int start = 0;
		std::vector<std::string> result;
		for (int i = 0; i < str.length(); ++i)
		{
			if (str[i] == split)
			{
				std::string sub = str.substr(start, i - start);
				result.push_back(sub);
				start = i + 1;
			}
		}
		result.push_back(str.substr(start, str.length() - start));
		return result;
	}
}