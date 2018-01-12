#pragma once
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <sstream>
#include <regex>
#include "./utils/logger.h"
#include "./utils/string.h"

namespace onodrim
{
	struct JSONObject
	{
		JSONObject(std::unordered_map<std::string, std::string> map)
		{
			Map = map;
		}
	private:
		std::unordered_map<std::string, std::string> Map;
	public:
		template <typename T>
		T Get(const std::string& key)
		{
			auto it = Map.find(key);
			if (it == Map.end())
			{
				return NULL;
			}
			std::stringstream convert(it->second);
			T result;
			convert >> result;
			return result;
		}

		template <typename T>
		std::vector<T> GetArray(const std::string& key)
		{
			auto it = Map.find(key);
			std::vector<T> result;
			if (it == Map.end())
			{
				return result;
			}
			
			auto values = utils::split(it->second.substr(1,it->second.length()-2), ',');
			for (auto& value : values)
			{
				std::stringstream convert(value);
				T castedValue;
				convert >> castedValue;
				result.push_back(castedValue);
			}
			return result;
		}

	};

	class JSON
	{
	public:
		static JSONObject parse(std::string& input)
		{
			std::string formatted = TrimString(input);
			LOG_DEBUG("JSON::CTOR = %s", formatted.c_str());
			int closingBracket = 0;
			/*
			std::vector<std::pair<int, int>> scopes;
			for (int i = 0; i < formatted.length(); i++)
			{
			if (formatted[i] == '{')
			{
			closingBracket = FindIndexOfClosingBracket(input, i);
			scopes.push_back(std::pair<int, int>(i, closingBracket));
			}
			}
			for (auto& scope : scopes)
			{

			}*/
			std::string removed = formatted.substr(1, formatted.length() - 2);
			LOG_DEBUG("Found: %s", removed.c_str());
			auto splitString = split(removed, ',');
			auto map = VectorToMap(splitString);
			return JSONObject{ map };
			//std::unordered_map<std::string, std::string> map;
			//onodrim::utils::log("JSON::CTOR scopes:");
		}

	protected:
		static int FindIndexOfClosingCharacter(std::string& input, int indexOfOpenBracket, char opening, char closing)
		{
			int level = 0;
			int length = input.length();
			if (indexOfOpenBracket == -1 || indexOfOpenBracket > length || input[indexOfOpenBracket] != opening)
			{
				return -1;
			}

			for (int i = indexOfOpenBracket + 1; i < length; i++)
			{
				if (input[i] == opening)
				{
					level++;
				}
				if (input[i] == closing)
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

		static std::vector<std::string> split(std::string& str, char split)
		{
			int start = 0;
			std::vector<std::string> result;
			for (int i = 0; i < str.length(); ++i)
			{
				if (str[i] == '[')
				{

					int index = FindIndexOfClosingCharacter(str, i, '[', ']');
					std::string sub = str.substr(start, index - start + 1);
					result.push_back(sub);
					i = index + 1;
					start = i + 1;
				}
				else if (str[i] == '{')
				{

					int index = FindIndexOfClosingCharacter(str, i, '{', '}');
					std::string sub = str.substr(start, index - start + 1);
					result.push_back(sub);
					i = index + 1;
					start = i + 1;
				}
				else if (str[i] == split)
				{
					std::string sub = str.substr(start, i - start);
					result.push_back(sub);
					start = i + 1;
				}
			}
			if (start != str.length())
			{
				result.push_back(str.substr(start, str.length() - start));
			}

			return result;
		}

		static std::vector<std::pair<std::string, std::string>> VectorToPair(std::vector<std::string> vector)
		{
			std::vector<std::pair<std::string, std::string>> result;
			for (auto& value : vector)
			{
				std::pair<std::string, std::string> pair;
				auto split = onodrim::utils::split(value, ':');
				pair.first = split[0];
				pair.second = split[1];
				result.push_back(pair);
			}
			return result;
		}
		static std::unordered_map<std::string, std::string> VectorToMap(std::vector<std::string> vector)
		{
			std::unordered_map<std::string, std::string> result;
			for (auto& value : vector)
			{
				std::pair<std::string, std::string> pair;
				auto splitString = onodrim::utils::split(value, ':');
				result[splitString[0]] = splitString[1];
			}
			return result;
		}

		static std::string TrimString(std::string& input)
		{
			static const std::regex regexSpaceTabNewline("[\\t\\s\\n\\r\"\']");
			return std::regex_replace(input, regexSpaceTabNewline, "");
		}
	};
}