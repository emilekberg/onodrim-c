#pragma once
#include <vector>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <istream>
#include <string>
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
			ParseString(formatted);
		}

		template <typename T>
		T Get(const std::string& key)
		{
			auto it = m_map.find(key);
			if (it == m_map.end())
			{
				return T();
			}
			std::stringstream ss(it->second);
			T result;
			ss >> std::noskipws >> result;
			return result;
		}
		template <>
		std::string Get<std::string>(const std::string& key)
		{
			auto it = m_map.find(key);
			if (it == m_map.end())
			{
				return "";
			}
			return it->second;
		}

		template <typename T>
		void Set(const std::string& key, const T& value)
		{
			std::stringstream convert;
			convert << std::noskipws << value;
			m_map[key] = convert.str();
		}

	protected:
		std::unordered_map<std::string, std::string> m_map;

	protected:
		static int FindIndexOfClosingCharacter(const std::string& input, int indexOfOpenBracket, char opening, char closing)
		{
			int level = 0;
			int length = input.length()-1;
			if (indexOfOpenBracket == -1 || indexOfOpenBracket > length || input[indexOfOpenBracket] != opening)
			{
				return -1;
			}

			for (int i = indexOfOpenBracket+1; i < length; ++i)
			{
				if (input[i] == opening && !(opening == closing))
				{
					++level;
				}
				else if (input[i] == closing)
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

		void ParseString(const std::string& str)
		{
			size_t start = 1;
			size_t length = str.length()-1;
			for (size_t i = start; i < length; ++i)
			{
				if (IsArray(str[i]))
				{
					int end = FindIndexOfClosingCharacter(str, i, '[', ']');
					std::string keyvalue = str.substr(start, end - start + 1);
					std::size_t found = keyvalue.find(':');
					m_map[keyvalue.substr(0, found)] = keyvalue.substr(found + 1, keyvalue.length() - found - 1);
					i = end + 1;
					start = i + 1;
				}
				else if (IsObject(str[i]))
				{

					int end = FindIndexOfClosingCharacter(str, i, '{', '}');
					std::string keyvalue = str.substr(start, end - start + 1);
					std::size_t found = keyvalue.find(':');
					m_map[keyvalue.substr(0, found)] = keyvalue.substr(found + 1, keyvalue.length() - found - 1);
					i = end + 1;
					start = i + 1;
				}
				else if (IsSeparator(str[i]))
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

		inline bool IsArray(const char a)
		{
			return a == '[';
		}

		inline bool IsObject(const char a)
		{
			return a == '{';
		}
		inline bool IsSeparator(const char a)
		{
			return a == ',';
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
			for (size_t i = 0; i < input.length(); ++i)
			{
				
				// keep formatting within quotationmarks (keys and strings)
				if (input[i] == '\"')
				{
					// would be nice to solve this in a different way
					if (num > 0)
					{
						i -= num;
						input.erase(i, num);
						num = 0;
					}
					size_t end = FindIndexOfClosingCharacter(input, i, '\"', '\"');
					input.erase(i, 1);
					input.erase(end-1, 1);
					i = end-2;
				}
				
				// increase buffer for removal if matches any of the to-remove signs
				if(compareWithData<toReplace.size()>(input[i], toReplace.data()))
				{
					num++;
				}
				else
				{
					// if we have some buffer to remove, remove them from the string.
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

	std::istream& operator>>(std::istream& is, JSON& object)
	{
		std::string s(std::istreambuf_iterator<char>(is), {});
		object.ParseRawString(s);
		return is;
	}

	template <typename T>
	std::istream& operator>>(std::istream& is, std::vector<T>& vector)
	{
		std::string s(std::istreambuf_iterator<char>(is), {});
		
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
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const JSON& object)
	{
		throw "NOT IMPLEMENTED";
		return os;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector)
	{
		os << '[';
		for (size_t i = 0, length = vector.size(); i < length; ++i)
		{
			os << vector[i];
			if (i < length-1)
			{
				os << ',';
			}
		}
		os << ']';
		return os;
	}
}