#define CATCH_CONFIG_MAIN
#include "../TV/CTVSet.h"
#include "../catch2/catch.hpp"

TEST_CASE("Test power function")
{
	CTVSet tv;
	REQUIRE(tv.IsTurnedOn() == false);
	tv.TurnOn();
	REQUIRE(tv.IsTurnedOn() == true);
	tv.TurnOff();
	REQUIRE(tv.IsTurnedOn() == false);
}

TEST_CASE("Test set numeric channel")
{
	SECTION("Tv is turned off")
	{
		CTVSet tv;
		tv.TurnOff();
		auto expectedCurrent = tv.GetCurrentChannel();
		REQUIRE(expectedCurrent == 0);
		REQUIRE(tv.SetChannel(1) == false);
		REQUIRE(expectedCurrent == tv.GetCurrentChannel());
		REQUIRE(tv.SetChannel(0) == false);
		REQUIRE(expectedCurrent == tv.GetCurrentChannel());
		REQUIRE(tv.SetChannel(-1) == false);
		REQUIRE(expectedCurrent == tv.GetCurrentChannel());
		REQUIRE(tv.SetChannel(100) == false);
		REQUIRE(expectedCurrent == tv.GetCurrentChannel());
	}

	SECTION("Tv is turned on")
	{
		CTVSet tv;
		tv.TurnOn();
		SECTION("Valid channel number")
		{
			REQUIRE(tv.GetCurrentChannel() == 1);
			REQUIRE(tv.SetChannel(50) == true);
			REQUIRE(tv.GetCurrentChannel() == 50);
			REQUIRE(tv.SetChannel(1) == true);
			REQUIRE(tv.GetCurrentChannel() == 1);
			REQUIRE(tv.SetChannel(99) == true);
			REQUIRE(tv.GetCurrentChannel() == 99);
		}
		SECTION("Invalid channel number")
		{
			REQUIRE(tv.SetChannel(99) == true);
			REQUIRE(tv.GetCurrentChannel() == 99);

			REQUIRE(tv.SetChannel(0) == false);
			REQUIRE(tv.GetCurrentChannel() == 99);
			REQUIRE(tv.SetChannel(-50) == false);
			REQUIRE(tv.GetCurrentChannel() == 99);
			REQUIRE(tv.SetChannel(100) == false);
			REQUIRE(tv.GetCurrentChannel() == 99);
		}
	}
}

TEST_CASE("Test channel alias name")
{
	SECTION("set channel name")
	{
		SECTION("Tv is turned off")
		{
			CTVSet tv;
			tv.TurnOff();
			REQUIRE(tv.SetChannelName(1, "first") == false);
		}
		SECTION("Tv is turned on")
		{
			CTVSet tv;
			tv.TurnOn();
			SECTION("Set valid channel alias")
			{
				REQUIRE(tv.SetChannelName(1, "First") == true);
				REQUIRE(tv.GetChannelName(1).value() == "First");
				REQUIRE(tv.GetChannelByName("First") == 1);
				REQUIRE(tv.SetChannelName(50, "Fivty channel") == true);
				REQUIRE(tv.GetChannelName(50).value() == "Fivty channe");
				REQUIRE(tv.GetChannelByName("Fivty channe") == 50);
				REQUIRE(tv.SetChannelName(99, "Ninety nine channel") == true);
				REQUIRE(tv.GetChannelName(99).value() == "Ninety nine channel");
				REQUIRE(tv.GetChannelByName("Ninety nine channel") == 99);
			}
			SECTION("Set invalid channel alias")
			{
				REQUIRE(tv.SetChannelName(0, "Zero") == false);
				REQUIRE(tv.GetChannelByName("Zero") == std::nullopt);
				REQUIRE(tv.GetChannelName(0) == std::nullopt);
				REQUIRE(tv.SetChannelName(5, "") == false);
				REQUIRE(tv.GetChannelByName("") == std::nullopt);
				REQUIRE(tv.GetChannelName(5) == std::nullopt);
			}
		}
	}
}
