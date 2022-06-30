#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "FindEx.h"
#include "MyArray.h"

TEST_CASE("Test findEx function")
{
	auto StringPredicate = [](const std::string& first, const std::string& second) -> bool { return first > second; };
	SECTION("Test with empty vector")
	{
		std::vector<std::string> test;
		std::string max;
		REQUIRE(task1::FindMax(test, max, StringPredicate) == false);
	}
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

TEST_CASE("Test MyArray<int> class")
{
	SECTION("Positive tests")
	{
		SECTION("Create empty")
		{
			MyArray<int> empty;
			REQUIRE(empty.GetSize() == 0);
			REQUIRE(empty.GetCapacity() == 0);
		}
		SECTION("Create from copy constructor")
		{
			MyArray<int> original;
			original.Append(1);
			original.Append(2);
			original.Append(3);
			MyArray test(original);
			REQUIRE(test.GetSize() == 3);
			REQUIRE(test.GetCapacity() == 3);
			REQUIRE(original.GetSize() == 3);
			REQUIRE(original.GetCapacity() == 4);
		}
		SECTION("Create from move constructor")
		{
			MyArray<int>&& original{};
			original.Append(1);
			original.Append(2);
			original.Append(3);
			MyArray<int> test(std::move(original));
			REQUIRE(test.GetSize() == 3);
			REQUIRE(test.GetCapacity() == 4);
			REQUIRE(original.GetSize() == 0);
			REQUIRE(original.GetCapacity() == 0);
		}
		SECTION("Check resize")
		{
			MyArray<int> empty;
			empty.Resize(5);
			REQUIRE(empty.GetSize() == 0);
			REQUIRE(empty.GetCapacity() == 5);
		}
		SECTION("Check append")
		{
			MyArray<int> empty;
			empty.Append(5);
			REQUIRE(empty.GetSize() == 1);
			REQUIRE(empty.GetCapacity() == 1);
			empty.Append(42);
			REQUIRE(empty.GetSize() == 2);
			REQUIRE(empty.GetCapacity() == 2);
			empty.Append(42);
			REQUIRE(empty.GetSize() == 3);
			REQUIRE(empty.GetCapacity() == 4);
		}
		SECTION("Check copy operator")
		{
			MyArray<int> test;
			MyArray<int> original;
			original.Append(1);
			original.Append(2);
			original.Append(3);
			test = original;
			REQUIRE(test.GetSize() == 3);
			REQUIRE(test.GetCapacity() == 3);
			REQUIRE(original.GetSize() == 3);
			REQUIRE(original.GetCapacity() == 4);
		}
		SECTION("Check move operator")
		{
			MyArray<int> test;
			MyArray<int> original;
			original.Append(1);
			original.Append(2);
			original.Append(3);
			test = std::move(original);
			REQUIRE(test.GetSize() == 3);
			REQUIRE(test.GetCapacity() == 4);
			REQUIRE(original.GetSize() == 0);
			REQUIRE(original.GetCapacity() == 0);
		}
		SECTION("Check index access")
		{
			MyArray<int> original;
			original.Append(1);
			original.Append(2);
			original.Append(3);
			const auto& constItem = original[1];
			REQUIRE(constItem == 2);
			auto& item = original[0];
			REQUIRE(item == 1);
		}
		SECTION("Check clear")
		{
			MyArray<int> original;
			original.Append(1);
			original.Append(2);
			original.Append(3);
			REQUIRE(original.GetSize() == 3);
			REQUIRE(original.GetCapacity() == 4);
			original.Clear();
			REQUIRE(original.GetSize() == 0);
			REQUIRE(original.GetCapacity() == 0);
		}
		SECTION("Check iterators")
		{
			MyArray<int> original;
			original.Append(1);
			original.Append(2);
			original.Append(3);

			REQUIRE(*original.begin() == 1);
			REQUIRE(*(++original.begin()) == 2);
			REQUIRE(*(--original.end()) == 3);
			REQUIRE(*(original.rbegin()) == 3);
			REQUIRE(*(++original.rbegin()) == 2);
			REQUIRE(*(--original.rend()) == 1);
		}
	}
	SECTION("Negative tests")
	{
		SECTION("Bad alloc")
		{
			MyArray<int> test;
			test.Append(1);
			test.Append(2);
			test.Append(3);
			REQUIRE(test.GetSize() == 3);
			REQUIRE(test.GetCapacity() == 4);
			REQUIRE_THROWS(test.Resize(999999999));
			REQUIRE(test.GetSize() == 3);
			REQUIRE(test.GetCapacity() == 4);
		}
		SECTION("Index out of range")
		{
			MyArray<int> test;
			test.Append(1);
			test.Append(2);
			test.Append(3);
			REQUIRE_THROWS(test[3]);
		}
	}
}
