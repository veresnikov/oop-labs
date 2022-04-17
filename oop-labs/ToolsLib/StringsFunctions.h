#pragma once
#include "pch.h"

class StringsFunctions
{
public:
	static std::string RemoveExtraSpaces(std::string const& arg);
	static std::string Trim(std::string const& arg);
private:
	static std::string LeftTrim(std::string const& arg);
	static std::string RightTrim(std::string const& arg);
	static std::string RemoveSpacesInsideString(std::string const& arg);
};