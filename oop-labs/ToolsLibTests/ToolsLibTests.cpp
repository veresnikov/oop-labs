#define CATCH_CONFIG_MAIN
#include "..\ToolsLib\StringsFunctions.h"
#include "..\ToolsLib\MapFunctions.h"
#include "..\catch2\catch.hpp"
#include <vector>

TEST_CASE("Test empty string")
{
	std::string input;
	std::string expected;
	REQUIRE(expected == StringsFunctions::RemoveExtraSpaces(input));
}

TEST_CASE("Test a single character string")
{
	std::string input = "a";
	std::string expected = "a";
	REQUIRE(expected == StringsFunctions::RemoveExtraSpaces(input));
}

TEST_CASE("Test a spaces around character string")
{
	std::string input = "    a     ";
	std::string expected = "a";
	REQUIRE(expected == StringsFunctions::RemoveExtraSpaces(input));
}

TEST_CASE("Test a extra spaces in string")
{
	std::string input = "42        42           42";
	std::string expected = "42 42 42";
	REQUIRE(expected == StringsFunctions::RemoveExtraSpaces(input));
}

TEST_CASE("Test with extra spaces in and around a string")
{
	std::string input = "           42        42           42 ";
	std::string expected = "42 42 42";
	REQUIRE(expected == StringsFunctions::RemoveExtraSpaces(input));
}

TEST_CASE("Test spaces string")
{
	std::string input = "         ";
	std::string expected = "";
	REQUIRE(expected == StringsFunctions::RemoveExtraSpaces(input));
}

TEST_CASE("Test find all")
{
	std::map<std::string, int> test = { { "one", 1 }, { "two", 2 }, { "three", 3 } };
	auto result = MapFunctions::FindAll(test.begin(), test.end(), [](std::pair<std::string, int> item) -> bool { return true; });
	REQUIRE(result.size() == 3);
}

TEST_CASE("Test find all 2")
{
	std::map<std::string, int> test = {
		{ "one", 1 },
		{ "two", 2 },
		{ "three", 3 },
		{ "two2", 2 },
	};
	auto result = MapFunctions::FindAll(test.begin(), test.end(), [](std::pair<std::string, int> item) -> bool { return item.second == 2; });
	REQUIRE(result.size() == 2);
}