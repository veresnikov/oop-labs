#define CATCH_CONFIG_MAIN
#include "../Time/Time.h"
#include "../catch2/catch.hpp"

TEST_CASE("Positive tests")
{
	SECTION("Construct in HH, MM, SS view")
	{
		Time time(4, 20, 30);
		REQUIRE(time.GetHours() == 4);
		REQUIRE(time.GetMinutes() == 20);
		REQUIRE(time.GetSeconds() == 30);

		Time zero(0, 0);
		REQUIRE(zero.GetHours() == 0);
		REQUIRE(zero.GetMinutes() == 0);
		REQUIRE(zero.GetSeconds() == 0);
	}
	SECTION("Construct in timestamp after midnight view")
	{
		Time time(15630);
		REQUIRE(time.GetHours() == 4);
		REQUIRE(time.GetMinutes() == 20);
		REQUIRE(time.GetSeconds() == 30);

		Time zero(0);
		REQUIRE(zero.GetHours() == 0);
		REQUIRE(zero.GetMinutes() == 0);
		REQUIRE(zero.GetSeconds() == 0);
	}
	SECTION("Arithmetic operators")
	{
		SECTION("add")
		{
			Time time(0);
			REQUIRE(time.GetHours() == 0);
			REQUIRE(time.GetMinutes() == 0);
			REQUIRE(time.GetSeconds() == 0);

			++time;
			REQUIRE(time.GetHours() == 0);
			REQUIRE(time.GetMinutes() == 0);
			REQUIRE(time.GetSeconds() == 1);

			auto temp = time++;
			REQUIRE(time.GetHours() == 0);
			REQUIRE(time.GetMinutes() == 0);
			REQUIRE(time.GetSeconds() == 2);
			REQUIRE(temp.GetSeconds() == 1);

			temp = time + temp;
			REQUIRE(temp.GetHours() == 0);
			REQUIRE(temp.GetMinutes() == 0);
			REQUIRE(temp.GetSeconds() == 3);

			temp += Time(1,0,0);
			REQUIRE(temp.GetHours() == 1);
			REQUIRE(temp.GetMinutes() == 0);
			REQUIRE(temp.GetSeconds() == 3);
		}
		SECTION("sub")
		{
			Time time(0);
			REQUIRE(time.GetHours() == 0);
			REQUIRE(time.GetMinutes() == 0);
			REQUIRE(time.GetSeconds() == 0);

			--time;
			REQUIRE(time.GetHours() == 23);
			REQUIRE(time.GetMinutes() == 59);
			REQUIRE(time.GetSeconds() == 59);

			auto temp = time--;
			REQUIRE(time.GetHours() == 23);
			REQUIRE(time.GetMinutes() == 59);
			REQUIRE(time.GetSeconds() == 58);
			REQUIRE(temp.GetSeconds() == 59);

			temp = temp - time;
			REQUIRE(temp.GetHours() == 0);
			REQUIRE(temp.GetMinutes() == 0);
			REQUIRE(temp.GetSeconds() == 1);

			temp -= Time(1, 0, 0);
			REQUIRE(temp.GetHours() == 23);
			REQUIRE(temp.GetMinutes() == 0);
			REQUIRE(temp.GetSeconds() == 1);
		}
		SECTION("mul")
		{
			Time time(0, 1, 1);
			REQUIRE(time.GetHours() == 0);
			REQUIRE(time.GetMinutes() == 1);
			REQUIRE(time.GetSeconds() == 1);

			time *= 2;
			REQUIRE(time.GetHours() == 0);
			REQUIRE(time.GetMinutes() == 2);
			REQUIRE(time.GetSeconds() == 2);

			auto temp = time * 2;
			REQUIRE(temp.GetHours() == 0);
			REQUIRE(temp.GetMinutes() == 4);
			REQUIRE(temp.GetSeconds() == 4);

			temp = 2 * temp;
			REQUIRE(temp.GetHours() == 0);
			REQUIRE(temp.GetMinutes() == 8);
			REQUIRE(temp.GetSeconds() == 8);

			temp = 0 * time;
			REQUIRE(temp.GetHours() == 0);
			REQUIRE(temp.GetMinutes() == 0);
			REQUIRE(temp.GetSeconds() == 0);
		}
		SECTION("div")
		{
			Time time(9, 15, 40);
			REQUIRE(time.GetHours() == 9);
			REQUIRE(time.GetMinutes() == 15);
			REQUIRE(time.GetSeconds() == 40);

			auto temp = time / 3;
			REQUIRE(temp.GetHours() == 3);
			REQUIRE(temp.GetMinutes() == 5);
			REQUIRE(temp.GetSeconds() == 13);

			time /= 3;
			REQUIRE(time.GetHours() == 3);
			REQUIRE(time.GetMinutes() == 5);
			REQUIRE(time.GetSeconds() == 13);

			REQUIRE(Time(9, 15, 40) / Time(3, 5, 13) == 3);
		}
	}
}
