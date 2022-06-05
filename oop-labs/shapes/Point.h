#pragma once
#include <cmath>
#include <ostream>

struct Point
{
	double x;
	double y;

	[[nodiscard]] double GetLine(const Point& second) const;
	friend std::ostream& operator<<(std::ostream& output, const Point& point);
};

inline std::ostream& operator<<(std::ostream& output, const Point& point)
{
	output << "{" << point.x << "," << point.y << "}";
	return output;
}

inline double Point::GetLine(const Point& second) const
{
	return std::sqrt(std::pow(x - second.x, 2) + std::pow(y - second.y, 2));
}

