#pragma once
#include <string>
class JSON
{
public:
	JSON(std::string& input);
	~JSON();

protected:
	int FindIndexOfClosingBracket(int start);
	std::string TrimString(std::string& input);

	std::string m_Buffer;
};

