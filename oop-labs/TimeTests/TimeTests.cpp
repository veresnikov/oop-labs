#define CATCH_CONFIG_MAIN
#include "../Time/Time.h"
#include "../catch2/catch.hpp"

TEST_CASE("Example")
{
	try
	{
		Time t(9, 15, 40);
		std::cout << t / Time(03, 05, 13) << std::endl;

	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	//std::cout << t.GetHours() << ":" << t.GetMinutes() << ":" << t.GetSeconds() << std::endl;

	REQUIRE(true);
}
