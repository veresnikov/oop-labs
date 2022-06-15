#pragma once
#include <cmath>
#include <numbers>
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

// todo вынести
inline float Point::GetLine(const Point& second) const
{
	return static_cast<float>(std::sqrt(std::pow(x - second.x, 2) + std::pow(y - second.y, 2)));
}

inline Point GetVector(Point start, Point end)
{
	return { end.x - start.x, end.y - start.y };
}

inline float Dot(Point start, Point end)
{
	return start.x * end.x + start.y * end.y;
}

inline float Norm(Point point)
{
	return std::sqrtf(point.x * point.x + point.y * point.y);
}

inline float GetAngle(Point start, Point end)
{
	float cosAngle = Dot(start, end) / (Norm(start) * Norm(end));
	if (cosAngle > 1.0)
		return 0.0;
	else if (cosAngle < -1.0)
		return static_cast<float>(std::numbers::pi);
	return std::acosf(cosAngle);
}