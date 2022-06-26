#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "FindEx.h"


TEST_CASE("Test findEx function")
{
	auto StringPredicate = [](const std::string& first, const std::string& second) -> bool { return first > second; };
	SECTION("Test with 1 item in vector")
	{
		std::vector<std::string> test{ "test" };
		std::string max;
		REQUIRE(task1::FindMax(test, max, StringPredicate));
		REQUIRE(max == test[0]);
	}
	SECTION("Test with 3 item in vector")
	{
		std::vector<std::string> test{
			"cccc",
			"aaaa",
			"bbbb",
		};
		std::string max;
		REQUIRE(task1::FindMax(test, max, StringPredicate));
		REQUIRE(max == test[1]);
	}
	SECTION("Test with struct")
	{
		struct Person
		{
			std::string name;
			int age;
			int height;
			double weight;
		};

		std::vector<Person> test{
			{ "Ivan", 10, 115, 50 },
			{ "Nikolay", 14, 171, 63 },
			{ "Kirill", 22, 170, 70 },
			{ "Petr", 10, 110, 80 },
		};
		Person oldest;
		REQUIRE(task1::FindMax(test, oldest, [](const Person& first, const Person& second) -> bool { return first.age < second.age; }));
		REQUIRE(oldest.name == "Kirill");
		REQUIRE(oldest.age == 22);

		Person high;
		REQUIRE(task1::FindMax(test, high, [](const Person& first, const Person& second) -> bool { return first.height < second.height; }));
		REQUIRE(high.name == "Nikolay");
		REQUIRE(high.height == 171);

		Person fat;
		REQUIRE(task1::FindMax(test, fat, [](const Person& first, const Person& second) -> bool { return first.weight < second.weight; }));
		REQUIRE(fat.name == "Petr");
		REQUIRE(fat.weight == 80);
	}
}
