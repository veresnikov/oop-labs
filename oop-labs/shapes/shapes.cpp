#include <iostream>
#include "ShapesParser.h"


void Parse(const ShapesParser& parser, const std::string& input, std::vector<std::shared_ptr<IShape>>& output)
{
	try
	{
		parser.Parse(input);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
}

void PrintShapesInfo(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	if (shapes.empty())
	{
		std::cout << "Empty" << std::endl;
		return;

	}
	for (auto shape : shapes)
	{
		std::cout << shape->ToString() << std::endl;	
	}
}

void Help()
{
	std::cout << "Available command:" << std::endl;
	std::cout << "printInfo" << std::endl;
	std::cout << "Shapes example command:" << std::endl;
	std::cout << "line {x,y} {x,y} ffffff (line width)" << std::endl;
	std::cout << "rectangle {x,y} {x,y} ffffff (line width) ffffff" << std::endl;
	std::cout << "triangle {x,y} {x,y} {x,y} ffffff (line width) ffffff" << std::endl;
	std::cout << "circle {x,y} r ffffff (line width) ffffff" << std::endl;
	std::cout << "exit" << std::endl;
}

int main()
{
	ShapesParser parser;
	std::vector<std::shared_ptr<IShape>> shapes;
	while (true)
	{
		std::string input;
		std::cin >> input;
		if (input == "help")
		{
			Help();
		}
		else if (input == "exit")
		{
			break;
		}
		else if (input == "printInfo")
		{
			PrintShapesInfo(shapes);
		}
		else
		{
			Parse(parser, input, shapes);
		}
	}
	
}