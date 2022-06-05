#include <iostream>
#include "ShapesParser.h"

int main()
{
	ShapesParser parser;
	try
	{
		auto line = parser.Parse("line {100,101} {200,200.5} ffffff 3.5");
		auto rectangle = parser.Parse("rectangle {100,100} {200,200.5} fff32f 4 123456");
		auto triangle = parser.Parse("triangle {1,1} {4,4} {0.5,3} fff32f 4 123456");
		auto circle = parser.Parse("circle {0,0} 10.679 fff32f 4 123456");

		std::cout << line->ToString() << std::endl;
		std::cout << rectangle->ToString() << std::endl;
		std::cout << triangle->ToString() << std::endl;
		std::cout << circle->ToString() << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
}