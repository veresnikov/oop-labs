#define CATCH_CONFIG_MAIN
#include "../ToolsLib/MapFunctions.h"
#include "../ToolsLib/StringsFunctions.h"
#include "../catch2/catch.hpp"
#include <vector>

TEST_CASE("Test empty string")
{
	const std::string input;
	const std::string expected;
	REQUIRE(expected == StringsFunctions::RemoveExtraSpaces(input));
}

TEST_CASE("Test a single character string")
{
	const std::string input = "a";
	const std::string expected = "a";
	REQUIRE(expected == StringsFunctions::RemoveExtraSpaces(input));
}

TEST_CASE("Test a spaces around character string")
{
	const std::string input = "    a     ";
	const std::string expected = "a";
	REQUIRE(expected == StringsFunctions::RemoveExtraSpaces(input));
}

TEST_CASE("Test a extra spaces in string")
{
	const std::string input = "42        42           42";
	const std::string expected = "42 42 42";
	REQUIRE(expected == StringsFunctions::RemoveExtraSpaces(input));
}

TEST_CASE("Test with extra spaces in and around a string")
{
	const std::string input = "           42        42           42 ";
	const std::string expected = "42 42 42";
	REQUIRE(expected == StringsFunctions::RemoveExtraSpaces(input));
}

TEST_CASE("Test spaces string")
{
	const std::string input = "         ";
	const std::string expected;
	REQUIRE(expected == StringsFunctions::RemoveExtraSpaces(input));
}

TEST_CASE("Test explode string")
{
	const std::vector<std::string> expected{ "one", "two", "three", "four" };
	const std::string input = "one two three four";
	REQUIRE(expected == StringsFunctions::Explode(input, " "));
}

TEST_CASE("Test explode string with one words")
{
	const std::vector<std::string> expected{ "one" };
	const std::string input = "one";
	REQUIRE(expected == StringsFunctions::Explode(input, " "));
}

TEST_CASE("Test find all")
{
	std::map<std::string, int> test = { { "one", 1 }, { "two", 2 }, { "three", 3 } };
	const auto result = MapFunctions::FindAll(test.begin(), test.end(), [](const std::pair<std::string, int>& item) -> bool { return true; });
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
	const auto result = MapFunctions::FindAll(test.begin(), test.end(), [](const std::pair<std::string, int>& item) -> bool { return item.second == 2; });
	REQUIRE(result.size() == 2);
}

TEST_CASE("Test sort map by value")
{
	const std::map<std::string, int> test = {
		{ "two", 2 },
		{ "three", 3 },
		{ "one", 1 }
	};
	const std::vector<std::pair<std::string, int>> expected{
		{ "one", 1 },
		{ "two", 2 },
		{ "three", 3 },
	};
	const auto result = MapFunctions::Sort(test, [](const std::pair<std::string, int>& first, const std::pair<std::string, int>& second) -> bool { return first.second < second.second; });
	REQUIRE(expected.size() == result.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		REQUIRE(expected[i].first == result[i].first);
		REQUIRE(expected[i].second == result[i].second);
	}
}
