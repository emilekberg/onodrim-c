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
#include <istream>
namespace onodrim
{
	class JSON
	{
	public:
		JSON()
		{

		}
		JSON(std::string& input)
		{
			ParseRawString(input);
		}

		void ParseRawString(std::string& input)
		{
			std::string formatted = TrimString(input);
			std::string removed = formatted.substr(1, formatted.length() - 2);
			parseString(removed, ',');
		}

		static std::shared_ptr<JSON> parse(std::string& input)
		{
			return std::make_shared<JSON>(input);
		}

		template <typename T>
		T Get(const std::string& key)
		{
			auto it = m_map.find(key);
			if (it == m_map.end())
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
			auto it = m_map.find(key);
			std::vector<T> result;
			if (it == m_map.end())
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
			auto it = m_map.find(key);
			std::vector<std::shared_ptr<JSON>> result;
			if (it == m_map.end())
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
			auto it = m_map.find(key);
			std::shared_ptr<JSON> result;
			if (it == m_map.end())
			{
				return nullptr;
			}

			result = std::make_shared<JSON>(it->second);
			return result;
		}

	protected:
		std::unordered_map<std::string, std::string> m_map;

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

		void parseString(std::string& str, char split)
		{
			size_t start = 0;
			for (size_t i = 0; i < str.length(); ++i)
			{
				if (str[i] == '[')
				{
					int end = FindIndexOfClosingCharacter(str, i, '[', ']');
					std::string keyvalue = str.substr(start, end - start + 1);
					std::size_t found = keyvalue.find(':');
					m_map[keyvalue.substr(0, found)] = keyvalue.substr(found + 1, keyvalue.length() - found - 1);
					i = end + 1;
					start = i + 1;
				}
				else if (str[i] == '{')
				{

					int end = FindIndexOfClosingCharacter(str, i, '{', '}');
					std::string keyvalue = str.substr(start, end - start + 1);
					std::size_t found = keyvalue.find(':');
					m_map[keyvalue.substr(0, found)] = keyvalue.substr(found + 1, keyvalue.length() - found - 1);
					i = end + 1;
					start = i + 1;
				}
				else if (str[i] == split)
				{
					std::string keyvalue = str.substr(start, i - start);
					std::size_t found = keyvalue.find(':');
					m_map[keyvalue.substr(0, found)] = keyvalue.substr(found + 1, keyvalue.length() - found - 1);
					start = i + 1;
				}
			}
			if (start < str.length())
			{
				std::string keyvalue = str.substr(start, str.length() - start);
				std::size_t found = keyvalue.find(':');
				m_map[keyvalue.substr(0, found)] = keyvalue.substr(found + 1, keyvalue.length() - found - 1);
			}
		}

		static std::unordered_map<std::string, std::string> VectorToMap(std::vector<std::string> vector)
		{
			std::unordered_map<std::string, std::string> result;
			for (auto& value : vector)
			{
				std::size_t found = value.find(':');
				result[value.substr(0, found)] = value.substr(found+1, value.length()-found-1);
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