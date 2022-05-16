#define CATCH_CONFIG_MAIN
#include "../TV/CTVSet.h"
#include "../catch2/catch.hpp"

TEST_CASE("Test power functions")
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
				REQUIRE(tv.SetChannelName(1, "One") == true);
				REQUIRE(tv.GetChannelName(1).value() == "One");
				REQUIRE(tv.GetChannelByName("One") == 1);
				REQUIRE(tv.SetChannelName(5, "One") == true);
				REQUIRE(tv.GetChannelName(5).value() == "One");
				REQUIRE(tv.GetChannelByName("One") == 5);
				REQUIRE(tv.SetChannelName(50, "Fivty channel") == true);
				REQUIRE(tv.GetChannelName(50).value() == "Fivty channel");
				REQUIRE(tv.GetChannelByName("Fivty channel") == 50);
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
	SECTION("select channel by name")
	{
		CTVSet tv;
		tv.TurnOn();
		tv.SetChannelName(1, "First");
		tv.SetChannelName(2, "Two");
		tv.SetChannelName(3, "Three");
		tv.SetChannelName(4, "Four");
		tv.SetChannelName(5, "Five");

		SECTION("Tv is turned off")
		{
			tv.TurnOff();
			auto expectedCurrent = tv.GetCurrentChannel();
			REQUIRE(expectedCurrent == 0);
			REQUIRE(tv.SetChannel("First") == false);
			REQUIRE(expectedCurrent == tv.GetCurrentChannel());
			REQUIRE(tv.SetChannel("") == false);
			REQUIRE(expectedCurrent == tv.GetCurrentChannel());
			REQUIRE(tv.SetChannel("KekTV") == false);
			REQUIRE(expectedCurrent == tv.GetCurrentChannel());
		}
		SECTION("Tv is turned on")
		{
			tv.TurnOn();
			SECTION("Valid channel name")
			{
				REQUIRE(tv.SetChannel("First") == true);
				REQUIRE(tv.GetCurrentChannel() == 1);
				REQUIRE(tv.SetChannel("Five") == true);
				REQUIRE(tv.GetCurrentChannel() == 5);
				REQUIRE(tv.SetChannel("Two") == true);
				REQUIRE(tv.GetCurrentChannel() == 2);
			}
			SECTION("Invalid channel name")
			{
				auto expectedCurrent = tv.GetCurrentChannel();
				REQUIRE(tv.SetChannel("KekTV") == false);
				REQUIRE(expectedCurrent == tv.GetCurrentChannel());
				REQUIRE(tv.SetChannel("") == false);
				REQUIRE(expectedCurrent == tv.GetCurrentChannel());
			}
		}
	}
	SECTION("get alias list")
	{
		SECTION("list not empty")
		{
			CTVSet tv;
			tv.TurnOn();
			tv.SetChannelName(1, "First");
			tv.SetChannelName(2, "Two");
			tv.SetChannelName(3, "Three");
			tv.SetChannelName(4, "Four");
			tv.SetChannelName(5, "Five");

			const std::vector<std::pair<std::string, int>> expected{
				{ "First", 1 },
				{ "Two", 2 },
				{ "Three", 3 },
				{ "Four", 4 },
				{ "Five", 5 },
			};
			SECTION("Tv is turned off")
			{
				tv.TurnOff();
				REQUIRE(tv.GetChannelAliasList() == std::nullopt);
			}
			SECTION("Tv is turned on")
			{
				tv.TurnOn();
				auto list = tv.GetChannelAliasList();
				REQUIRE(list != std::nullopt);
				REQUIRE(expected == list.value());
			}
		}
		SECTION("list empty")
		{
			CTVSet tv;
			tv.TurnOn();

			SECTION("Tv is turned off")
			{
				tv.TurnOff();
				REQUIRE(tv.GetChannelAliasList() == std::nullopt);
			}
			SECTION("Tv is turned on")
			{
				tv.TurnOn();
				auto list = tv.GetChannelAliasList();
				REQUIRE(list != std::nullopt);
				REQUIRE(list.value().empty());
			}
		}
	}
	SECTION("delete channel name")
	{
		CTVSet tv;
		tv.TurnOn();
		tv.SetChannelName(1, "First");
		tv.SetChannelName(2, "Two");
		tv.SetChannelName(3, "Three");
		tv.SetChannelName(4, "Four");
		tv.SetChannelName(5, "Five");

		SECTION("Tv is turned off")
		{
			tv.TurnOff();
			REQUIRE(tv.DeleteChannelName("First") == false);
			REQUIRE(tv.DeleteChannelName("") == false);
			REQUIRE(tv.DeleteChannelName("KekTV") == false);
		}
		SECTION("Tv is turned on")
		{
			tv.TurnOn();
			SECTION("Valid channel name")
			{
				REQUIRE(tv.DeleteChannelName("First") == true);
				REQUIRE(tv.GetChannelByName("First") == std::nullopt);
				REQUIRE(tv.DeleteChannelName("Five") == true);
				REQUIRE(tv.GetChannelByName("Five") == std::nullopt);
			}
			SECTION("Invalid channel name")
			{
				REQUIRE(tv.DeleteChannelName("First") == true);
				REQUIRE(tv.GetChannelByName("First") == std::nullopt);

				REQUIRE(tv.DeleteChannelName("First") == false);
				REQUIRE(tv.DeleteChannelName("Kek") == false);
				REQUIRE(tv.DeleteChannelName("") == false);
			}
		}
	}
}

TEST_CASE("Test previous channel functions")
{
	CTVSet tv;
	SECTION("Tv is turned off")
	{
		tv.TurnOff();
		REQUIRE(tv.GetPreviousChannel() == 0);
		REQUIRE(tv.SelectPreviousChannel() == false);
	}
	SECTION("Tv is turned on")
	{
		tv.TurnOn();
		REQUIRE(tv.GetPreviousChannel() == 1);
		REQUIRE(tv.SelectPreviousChannel() == true);
		REQUIRE(tv.GetCurrentChannel() == 1);
		REQUIRE(tv.SetChannel(5) == true);
		REQUIRE(tv.GetCurrentChannel() == 5);
		REQUIRE(tv.GetPreviousChannel() == 1);
		REQUIRE(tv.SelectPreviousChannel() == true);
		REQUIRE(tv.GetCurrentChannel() == 1);
	}
}
