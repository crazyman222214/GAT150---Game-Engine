#include "EString.h"

std::string ToLower(const std::string& str)
{
	std::string lowerStr;
	lowerStr.resize(str.size());

	//Old c++
	//for (int i = 0; i < str.size(); i++)
	//{
	//	lowerStr[i] = std::tolower(str[i]);
	//}

	//Modern c++
	std::transform(str.begin(), str.end(), lowerStr.begin(),
		[](char c)
		{
			return std::tolower(c);
		});

	return lowerStr;
}

std::string ToUpper(const std::string& str)
{
	std::string upperStr;
	upperStr.resize(str.size());

	//Old c++
	//for (int i = 0; i < str.size(); i++)
	//{
	//	upperStr[i] = std::toupper(str[i]);
	//}

	//Modern c++
	std::transform(str.begin(), str.end(), upperStr.begin(),
		[](char c)
		{
			return std::toupper(c);
		});

	return upperStr;
}

bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2)
{
	if (str1.length() != str2.length()) return false;

	return std::equal(str1.begin(), str1.end(), str2.begin(),
		[](char c1, char c2)
		{
			return std::tolower(c1) == std::tolower(c2);
		});
}
