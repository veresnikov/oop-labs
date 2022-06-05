#pragma once
#include "ShapesFactory.h"
#include <regex>

class ShapesParser
{
public:
	std::shared_ptr<IShape> Parse(const std::string& input) const;

private:
	void assertColor(const std::string& color, uint32_t& output) const;
	void assertPoint(const std::string& point, Point& output) const;
	void assertDouble(const std::string& value, double& output) const;

	std::shared_ptr<LineSegment> ParseLineSegment (const std::vector<std::string>& params) const;
	std::shared_ptr<Rectangle> ParseRectangle(const std::vector<std::string>& params) const;
	std::shared_ptr<Triangle> ParseTriangle(const std::vector<std::string>& params) const;
	std::shared_ptr<Circle> ParseCircle(const std::vector<std::string>& params) const;
};
