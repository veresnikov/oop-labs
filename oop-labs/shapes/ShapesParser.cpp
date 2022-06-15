#include "ShapesParser.h"
#include "../ToolsLib/StringsFunctions.h"

std::shared_ptr<IShape> ShapesParser::Parse(const std::string& input) const
{
	const std::vector<std::string> params = StringsFunctions::Explode(input, " ");
	if (params.size() > 1)
	{
		const std::string type = params[0];
		if (type == "line")
		{
			return ParseLineSegment(params);
		}
		else if (type == "rectangle")
		{
			return ParseRectangle(params);
		}
		else if (type == "triangle")
		{
			return ParseTriangle(params);
		}
		else if (type == "circle")
		{
			return ParseCircle(params);
		}
		throw std::invalid_argument("Unknown shape type");
	}
	throw std::invalid_argument("Incorrect input string");
}

void ShapesParser::assertColor(const std::string& color, uint32_t& output) const
{
	const std::regex colorRegex("[[:xdigit:]]{6}");
	if (std::regex_match(color, colorRegex))
	{
		try
		{
			output = std::stoul(color, nullptr, 16);
			return;
		}
		catch (const std::exception& exception)
		{
			throw std::invalid_argument(std::string("Color parsing error: ", exception.what()));
		}
	}
	throw std::invalid_argument("Invalid color input");
}

void ShapesParser::assertPoint(const std::string& point, Point& output) const
{
	const std::regex pointInputRegex("\\{\\d*[.]?\\d+,\\d*[.]?\\d+\\}");
	if (std::regex_match(point, pointInputRegex))
	{
		try
		{
			const std::regex pointValueRegex("\\d*[.]?\\d+");
			const std::vector<std::string> values{
				std::sregex_token_iterator{ point.begin(), point.end(), pointValueRegex, 0 },
				std::sregex_token_iterator{}
			};

			if (values.size() == 2)
			{
				auto x = std::stof(values[0]);
				auto y = std::stof(values[1]);
				if (x < 0 || y < 0)
				{
					throw std::invalid_argument("Invalid value");
				}
				output = {
					x,
					y
				};
				return;
			}
			throw std::invalid_argument("Incorrect number of values");
		}
		catch (const std::exception& exception)
		{
			throw std::invalid_argument("Point parsing error: " + std::string(exception.what()));
		}
	}
	throw std::invalid_argument("Invalid point input");
}

void ShapesParser::assertFloat(const std::string& value, float& output) const
{
	const std::regex floatRegex(R"(\d*[.]?\d+)");
	if (std::regex_match(value, floatRegex))
	{
		try
		{
			auto v = std::stof(value);
			if (v < 0)
			{
				throw std::invalid_argument("Incorrect value");
			}
			output = v;
			return;
		}
		catch (const std::exception& exception)
		{
			throw std::invalid_argument("Double value parsing error: " + std::string(exception.what()));
		}
	}
	throw std::invalid_argument("Invalid double value input");
}

std::shared_ptr<LineSegment> ShapesParser::ParseLineSegment(const std::vector<std::string>& params) const
{
	if (params.size() != 4)
	{
		throw std::invalid_argument("Invalid line params");
	}
	Point startPoint;
	assertPoint(params[1], startPoint);
	Point endPoint;
	assertPoint(params[2], endPoint);
	uint32_t outlineColor;
	assertColor(params[3], outlineColor);
	return ShapesFactory::CreateLineSegment(startPoint, endPoint, outlineColor);
}

std::shared_ptr<Rectangle> ShapesParser::ParseRectangle(const std::vector<std::string>& params) const
{
	if (params.size() != 6)
	{
		throw std::invalid_argument("Invalid rectangle params");
	}
	Point topLeft;
	assertPoint(params[1], topLeft);
	Point bottomRight;
	assertPoint(params[2], bottomRight);
	uint32_t outlineColor;
	assertColor(params[3], outlineColor);
	float outlineWidth;
	assertFloat(params[4], outlineWidth);
	uint32_t fillColor;
	assertColor(params[5], fillColor);
	return ShapesFactory::CreateRectangle(topLeft, bottomRight, outlineColor, outlineWidth, fillColor);
}

std::shared_ptr<Triangle> ShapesParser::ParseTriangle(const std::vector<std::string>& params) const
{
	if (params.size() != 7)
	{
		throw std::invalid_argument("Invalid triangle params");
	}
	Point vertex1;
	assertPoint(params[1], vertex1);
	Point vertex2;
	assertPoint(params[2], vertex2);
	Point vertex3;
	assertPoint(params[3], vertex3);
	uint32_t outlineColor;
	assertColor(params[4], outlineColor);
	float outlineWidth;
	assertFloat(params[5], outlineWidth);
	uint32_t fillColor;
	assertColor(params[6], fillColor);
	return ShapesFactory::CreateTriangle(vertex1, vertex2, vertex3, outlineColor, outlineWidth, fillColor);
}

std::shared_ptr<Circle> ShapesParser::ParseCircle(const std::vector<std::string>& params) const
{
	if (params.size() != 6)
	{
		throw std::invalid_argument("Invalid circle params");
	}
	Point center;
	assertPoint(params[1], center);
	float radius;
	assertFloat(params[2], radius);
	uint32_t outlineColor;
	assertColor(params[3], outlineColor);
	float outlineWidth;
	assertFloat(params[4], outlineWidth);
	uint32_t fillColor;
	assertColor(params[5], fillColor);
	return ShapesFactory::CreateCircle(center, radius, outlineColor, outlineWidth, fillColor);
}
