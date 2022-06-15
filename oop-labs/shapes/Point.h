#pragma once
#include <cmath>
#include <ostream>

struct Point
{
	float x;
	float y;

	[[nodiscard]] float GetLine(const Point& second) const;
	friend std::ostream& operator<<(std::ostream& output, const Point& point);
};

inline std::ostream& operator<<(std::ostream& output, const Point& point)
{
	output << "{" << point.x << "," << point.y << "}";
	return output;
}


//todo вынести
inline float Point::GetLine(const Point& second) const
{
	return static_cast<float>(std::sqrt(std::pow(x - second.x, 2) + std::pow(y - second.y, 2)));
}

