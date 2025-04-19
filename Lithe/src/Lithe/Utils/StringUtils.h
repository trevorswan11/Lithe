#pragma once

#include <string>

namespace Lithe::Utils {

	const std::string WHITESPACE = " \n\r\t\f\v";

	static std::string string_ltrim(const std::string& s)
	{
		size_t start = s.find_first_not_of(WHITESPACE);
		return (start == std::string::npos) ? "" : s.substr(start);
	}

	static std::string string_rtrim(const std::string& s)
	{
		size_t end = s.find_last_not_of(WHITESPACE);
		return (end == std::string::npos) ? "" : s.substr(0, end + 1);
	}

	static std::string string_trim(const std::string& s) {
		return string_rtrim(string_ltrim(s));
	}

	static std::string ToLowerCase(const std::string& input) {
		std::string result = input;
		std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
			return std::tolower(c);
			}
		);
		return result;
	}

	static bool StringContains(const std::string& original, const std::string& toSearch, bool caseSensitive = true)
	{
		if (caseSensitive)
			return original.find(toSearch) != std::string::npos;
		else
			return ToLowerCase(original).find(ToLowerCase(toSearch)) != std::string::npos;
	}

}
