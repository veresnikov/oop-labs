#define CATCH_CONFIG_MAIN
#include "../Time/Time.h"
#include "../catch2/catch.hpp"

TEST_CASE("Example")
{
	try
	{
		Time t(9, 15, 40);
		std::stringstream ss("10:10:10");
		ss >> t;
		std::cout << t << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	//std::cout << t.GetHours() << ":" << t.GetMinutes() << ":" << t.GetSeconds() << std::endl;

	REQUIRE(true);
}
