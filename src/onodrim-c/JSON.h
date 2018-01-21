#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <regex>
#include <istream>
#include <algorithm>
#include <array>
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

		inline bool HasValues() const
		{
			return !m_map.empty();
		}

		void ParseRawString(std::string& input)
		{
			std::string formatted = TrimString(input);
			std::string removed = formatted.substr(1, formatted.length() - 2);
			ParseString(removed, ',');
		}

		template <typename T>
		T Get(const std::string& key)
		{
			auto it = m_map.find(key);
			if (it == m_map.end())
			{
				return T();
			}
			std::stringstream convert(it->second);
			T result;
			convert >> result;
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

			for (int i = indexOfOpenBracket + 1; i < length; ++i)
			{
				if (input[i] == opening)
				{
					++level;
				}
				if (input[i] == closing)
				{
					if (level == 0)
					{
						return i;
					}
					--level;
				}
			}
			return -1;
		}

		void ParseString(std::string& str, char split)
		{
			size_t start = 0;
			size_t length = str.length();
			for (size_t i = 0; i < length; ++i)
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
			if (start < length)
			{
				std::string keyvalue = str.substr(start, length - start);
				std::size_t found = keyvalue.find(':');
				m_map[keyvalue.substr(0, found)] = keyvalue.substr(found + 1, keyvalue.length() - found - 1);
			}
		}

		std::string TrimString(std::string input)
		{
			static const std::array<char, 6> toReplace = {
				'\t',
				' ',
				'\n',
				'\r',
				'\"',
				'\''
			};
			size_t num = 0;
			for (size_t i = 1; i < input.length(); ++i)
			{
				if(compareWithData<toReplace.size()>(input[i], toReplace.data()))
				// if(std::find(toReplace.begin(), toReplace.end(), input[i]) != toReplace.end())
				{
					num++;
				}
				else
				{
					if (num)
					{
						i -= num;
						input.erase(i, num);
					}
					num = 0;
				}
			}
			return input;
		}

	private:
		/*
			hacker helper methods to unroll the loop and inline it.
		*/
		template<int SIZE>
		__forceinline bool comparer(const char& a, const char* compare, int i)
		{
			return comparer<1>(a, compare, i) || comparer<SIZE - 1>(a, compare, i + 1);
		}

		template<>
		__forceinline bool comparer<1>(const char& a, const char* compare, int i)
		{
			return compare[i] == a;
		}
		template<int SIZE>
		__forceinline bool compareWithData(const char& a, const char* compare)
		{
			return comparer<SIZE>(a, compare, 0);
		}
	};

	std::istream& operator>>(std::istream& ss, JSON& object)
	{
		std::string s(std::istreambuf_iterator<char>(ss), {});
		object.ParseRawString(s);
		return ss;
	}

	template <typename T>
	std::istream& operator>>(std::istream& ss, std::vector<T>& vector)
	{
		std::string s(std::istreambuf_iterator<char>(ss), {});
		
		const char separator = ',';
		size_t start = 1;
		size_t length = s.length() - 2;
		for (size_t i = 1; i < length; ++i)
		{
			if (s[i] == separator)
			{
				std::stringstream convert(s.substr(start, i - start));
				T castedValue;
				convert >> castedValue;
				vector.push_back(castedValue);
				start = i + 1;
			}
		}
		std::stringstream convert(s.substr(start, (s.length() - 1) - start));
		T castedValue;
		convert >> castedValue;
		vector.push_back(castedValue);
		return ss;
	}
}