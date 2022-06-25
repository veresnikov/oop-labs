#define CATCH_CONFIG_MAIN
#include "../URL/HTTPUrl.h"
#include "../catch2/catch.hpp"

using namespace url;

TEST_CASE("test")
{
	HTTPUrl url("https://testdomain.com/dir/test.doc");
	std::cout << url.GetURL() << std::endl;
}
