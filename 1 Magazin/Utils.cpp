#include "Utils.h"

#include <cctype> // #include <ctype.h>

bool Utils::compareStr(const string& str_1, const string& str_2) const
{
	if (str_1.size() != str_2.size())
		return false;
	const auto& len = str_1.size();
	for (unsigned i = 0; i < len; ++i)
		if (tolower(str_1.at(i)) != tolower(str_2.at(i)))
			return false;
	return true;
}

bool Utils::isDouble(const string& str) const
{
	if (!str.size())
		return false;
	if (str.at(0) == '.' || str.at(str.size() - 1) == '.')
		return false;
	auto found{ false };
	auto begin{ false };
	for (const auto& chr : str)
	{
		if (!begin)
		{
			if (chr == '+' || chr == '-')
				continue;
			begin = true;
		}
		if (chr == '.')
		{
			if (found)
				return false;
			found = true;
		}
		else if (chr < '0' || chr > '9')
			return false;
	}
	return true;
}