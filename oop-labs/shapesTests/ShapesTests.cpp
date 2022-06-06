#define CATCH_CONFIG_MAIN
#include "../shapes/ShapesParser.h"
#include "../catch2/catch.hpp"

TEST_CASE("Test parsing shapes")
{
	ShapesParser parser;
	SECTION("Correct input")
	{
		std::string line("line {100.0,100.0} {200.1,200.0} fff123 3.5");
		auto lineShape = parser.Parse(line);
		REQUIRE(lineShape->ToString() == line);

		std::string rectangle("rectangle {100.0,100.0} {200.0,200.5} fff32f 4.0 123456");
		auto rectangleShape = parser.Parse(rectangle);
		REQUIRE(rectangleShape->ToString() == rectangle);

		std::string triangle("triangle {1.0,1.0} {4.0,4.0} {0.5,3.0} fff32f 4.0 123456");
		auto triangleShape = parser.Parse(triangle);
		REQUIRE(triangleShape->ToString() == triangle);

		std::string circle("circle {0.0,0.0} 10.6 fff32f 4.0 123456");
		auto circleShape = parser.Parse(circle);
		REQUIRE(circleShape->ToString() == circle);
	}
	SECTION("Incorrect input")
	{
		REQUIRE_THROWS_WITH(parser.Parse("unknown shapes"), "Unknown shape type");
		REQUIRE_THROWS_WITH(parser.Parse(""), "Incorrect input string");

		SECTION("Check asserts")
		{
			//Incorrect hex
			REQUIRE_THROWS_WITH(parser.Parse("line {100.0,100.0} {200.0,200.0} ffz123 1.0"), "Invalid color input");

			//Incorrect point
			REQUIRE_THROWS_WITH(parser.Parse("line {-100.0,100.0} {200.0,200.0} fff123 1.0"), "Invalid point input");
			REQUIRE_THROWS_WITH(parser.Parse("line {100,0,100.0} {200.0,200.0} fff123 1.0"), "Invalid point input");

			//Incorrect double value
			REQUIRE_THROWS_WITH(parser.Parse("line {100.0,100.0} {200.0,200.0} fff123 1,0"), "Invalid double value input");
			REQUIRE_THROWS_WITH(parser.Parse("line {100.0,100.0} {200.0,200.0} fff123 -1.0"), "Invalid double value input");
		}
		SECTION("Check shapes errors")
		{
			REQUIRE_THROWS_WITH(parser.Parse("line {100.0,100.0} {200.0,200.0} ffz123"), "Invalid line params");
			REQUIRE_THROWS_WITH(parser.Parse("rectangle {100.0,100.0} {200.0,200.0} ffz123"), "Invalid rectangle params");
			REQUIRE_THROWS_WITH(parser.Parse("triangle {100.0,100.0} {200.0,200.0} ffz123"), "Invalid triangle params");
			REQUIRE_THROWS_WITH(parser.Parse("circle {100.0,100.0} {200.0,200.0} ffz123"), "Invalid circle params");
		}
	}
}

TEST_CASE("Check shapes function")
{
	ShapesParser parser;
	std::string line("line {100.0,100.0} {200.1,200.0} fff123 3.5");
	auto lineShape = parser.Parse(line);

	std::string rectangle("rectangle {100.0,100.0} {200.0,200.5} fff32f 4.0 123456");
	auto rectangleShape = parser.Parse(rectangle);

	std::string triangle("triangle {1.0,1.0} {4.0,4.0} {0.5,3.0} fff32f 4.0 123456");
	auto triangleShape = parser.Parse(triangle);

	std::string circle("circle {0.0,0.0} 10.6 fff32f 4.0 123456");
	auto circleShape = parser.Parse(circle);

	SECTION("Get area")
	{
		REQUIRE(std::round(lineShape->GetArea()) == 141);
		REQUIRE(std::round(rectangleShape->GetArea()) == 10050);
		REQUIRE(std::round(triangleShape->GetArea()) == 4);
		REQUIRE(std::round(circleShape->GetArea()) == 353);
	}
	SECTION("Get perimeter")
	{
		REQUIRE(std::round(lineShape->GetPerimeter()) == 141);
		REQUIRE(std::round(rectangleShape->GetPerimeter()) == 401);
		REQUIRE(std::round(triangleShape->GetPerimeter()) == 10);
		REQUIRE(std::round(circleShape->GetPerimeter()) == 67);
	}
}