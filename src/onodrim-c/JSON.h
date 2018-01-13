#pragma once
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <sstream>
#include <regex>
#include "./utils/logger.h"
#include "./utils/string.h"
#include <memory>
namespace onodrim
{
	class JSON
	{
	public:
		JSON(std::string& input)
		{
			std::string formatted = TrimString(input);
			LOG_DEBUG("JSON::CTOR = %s", formatted.c_str());

			std::string removed = formatted.substr(1, formatted.length() - 2);
			LOG_DEBUG("Found: %s", removed.c_str());
			auto splitString = split(removed, ',');
			m_Map = VectorToMap(splitString);
		}

		static std::shared_ptr<JSON> parse(std::string& input)
		{
			return std::make_shared<JSON>(input);
		}

		template <typename T>
		T Get(const std::string& key)
		{
			auto it = m_Map.find(key);
			if (it == m_Map.end())
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
			auto it = m_Map.find(key);
			std::vector<T> result;
			if (it == m_Map.end())
			{
				return result;
			}

			auto values = utils::split(it->second.substr(1, it->second.length() - 2), ',');
			for (auto& value : values)
			{
				std::stringstream convert(value);
				T castedValue;
				convert >> castedValue;
				result.push_back(castedValue);
			}
			return result;
		}

		// TODO: refactor and make nicer less hacky
		std::vector<std::shared_ptr<JSON>> GetArrayObj(const std::string& key)
		{
			auto it = m_Map.find(key);
			std::vector<std::shared_ptr<JSON>> result;
			if (it == m_Map.end())
			{
				return result;
			}

			auto values = utils::split(it->second.substr(1, it->second.length() - 2), ',');
			for (auto& value : values)
			{
				std::shared_ptr<JSON> castValue = std::make_shared<JSON>(value);
				result.push_back(castValue);
			}
			return result;
		}

		std::shared_ptr<JSON> GetObject(const std::string& key)
		{
			auto it = m_Map.find(key);
			std::shared_ptr<JSON> result;
			if (it == m_Map.end())
			{
				return nullptr;
			}

			result = std::make_shared<JSON>(it->second);
			return result;
		}

	protected:
		std::unordered_map<std::string, std::string> m_Map;

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
			if (start < str.length())
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
				std::size_t found = value.find(':');
				result[value.substr(0, found)] = value.substr(found+1, value.length()-found-1);
				// auto splitString = onodrim::utils::split(value, ':');
				// result[splitString[0]] = splitString[1];
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