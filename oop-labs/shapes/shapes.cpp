#include "Canvas.h"
#include "ShapesParser.h"
#include <iostream>
#include <mutex>
#include <thread>

void Parse(const ShapesParser& parser, const std::string& input, std::vector<std::shared_ptr<IShape>>& output)
{
	try
	{
		output.push_back(parser.Parse(input));
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
	for (size_t i = 0; i < shapes.size(); ++i)
	{
		std::cout << shapes[i]->ToString() << std::endl;
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
	std::vector<std::shared_ptr<IShape>> shapes;
	std::thread windowThread([](std::vector<std::shared_ptr<IShape>>& shapes) -> void {
		sf::RenderWindow window(sf::VideoMode(800, 600), "Render");
		window.setActive(true);
		Canvas canvas(window);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear(sf::Color::White);
			for (size_t i = 0; i < shapes.size(); ++i)
			{
				shapes[i]->Draw(canvas);
			}
			window.display();
		}
	},
		std::ref(shapes));
	windowThread.detach();

	ShapesParser parser;
	while (true)
	{
		std::string input;
		std::getline(std::cin, input);
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