#include "pch.h"
#include "StringsFunctions.h"

std::string StringsFunctions::RemoveExtraSpaces(std::string const& arg)
{
	const std::string trimmed = Trim(arg);
	return RemoveSpacesInsideString(trimmed);
}

std::string StringsFunctions::Trim(std::string const& arg)
{
	const std::string leftTrimmed = LeftTrim(arg);
	return RightTrim(leftTrimmed);
}

std::vector<std::string> StringsFunctions::Explode(std::string const& input, std::string const& separator)
{
	std::vector<std::string> result;
	size_t position = 0;
	size_t separatorPosition = input.find(separator, position);
	if (separatorPosition == std::string::npos)
	{
		result.push_back(input);
		return result;
	}

	while (position < input.length())
	{
		separatorPosition = input.find(separator, position);
		if (separatorPosition == std::string::npos)
		{
			result.push_back(input.substr(position));
			break;
		}
		result.push_back(input.substr(position, separatorPosition - position));
		position = separatorPosition + separator.length();
	}
	return result;
}

std::string StringsFunctions::LeftTrim(std::string const& arg)
{
	std::string result = arg;
	result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](const unsigned char ch) { return !std::isspace(ch); }));
	return result;
}

std::string StringsFunctions::RightTrim(std::string const& arg)
{
	std::string result = arg;
	result.erase(std::find_if(result.rbegin(), result.rend(), [](const unsigned char ch) { return !std::isspace(ch); }).base(), result.end());
	return result;
}

std::string StringsFunctions::RemoveSpacesInsideString(std::string const& arg)
{
	std::string result = arg;
	result.erase(std::unique_copy(arg.begin(), arg.end(), result.begin(), [](const unsigned char ch1, const unsigned char ch2) -> bool {
		return std::isspace(ch1) && std::isspace(ch2);
	}),
		result.end());
	return result;
}
