#include "JSON.h"
#include <regex>
#include "./utils/logger.h"
#include <vector>
#include <unordered_map>
JSON::JSON(std::string& input) : m_Buffer(TrimString(input))
{
	onodrim::utils::log("JSON::CTOR = %s",m_Buffer.c_str());
	int start = 35;
	int closingBracket = FindIndexOfClosingBracket(start);


	std::vector<std::pair<int, int>> scopes;
	for (int i = 0; i < m_Buffer.length(); i++)
	{
		if (m_Buffer[i] == '{')
		{
			closingBracket = FindIndexOfClosingBracket(i);
			scopes.push_back(std::pair<int, int>(i, closingBracket));
		}
	}
	//std::unordered_map<std::string, std::string> map;
	//onodrim::utils::log("JSON::CTOR scopes:");
}

JSON::~JSON()
{
}

int JSON::FindIndexOfClosingBracket(int indexOfOpenBracket)
{
	int level = 0;
	int length = m_Buffer.length();
	if (indexOfOpenBracket == -1 || indexOfOpenBracket > length || m_Buffer[indexOfOpenBracket] != '{')
	{
		return -1;
	}
	
	for (int i = indexOfOpenBracket+1; i < length; i++)
	{
		if (m_Buffer[i] == '{')
		{
			level++;
		}
		if (m_Buffer[i] == '}')
		{
			if (level == 0)
			{
				return i;
			}
			level--;
		}
	}
	return -1;
}

std::string JSON::TrimString(std::string& input)
{
	static const std::regex regexSpaceTabNewline("[\\t\\s\\n\\r]");
	return std::regex_replace(input, regexSpaceTabNewline, "");
}