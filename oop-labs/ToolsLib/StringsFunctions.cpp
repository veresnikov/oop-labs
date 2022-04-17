#include "pch.h"
#include "StringsFunctions.h"

std::string StringsFunctions::RemoveExtraSpaces(std::string const& arg)
{
	std::string trimmed = Trim(arg);
	return RemoveSpacesInsideString(trimmed);
}

std::string StringsFunctions::Trim(std::string const& arg)
{
	std::string leftTrimmed = LeftTrim(arg);
	return RightTrim(leftTrimmed);
}

std::string StringsFunctions::LeftTrim(std::string const& arg)
{
	std::string result = arg;
	result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) { return !std::isspace(ch); }));
	return result;
}

std::string StringsFunctions::RightTrim(std::string const& arg)
{
	std::string result = arg;
	result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), result.end());
	return result;
}

std::string StringsFunctions::RemoveSpacesInsideString(std::string const& arg)
{
	std::string result = arg;
	result.erase(std::unique_copy(arg.begin(), arg.end(), result.begin(), [](unsigned char ch1, unsigned char ch2) -> bool {
		return std::isspace(ch1) && std::isspace(ch2);
	}),
		result.end());
	return result;
}
