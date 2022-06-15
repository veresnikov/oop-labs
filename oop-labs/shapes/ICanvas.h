#pragma once
#include "Point.h"
#include <cstdint>
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void DrawLine(Point start, Point end, float width, uint32_t color) = 0;
	virtual void DrawPolygon(std::vector<Point> points, float width, uint32_t color) = 0;
	virtual void FillPolygon(std::vector<Point> points, uint32_t color) = 0;
	virtual void DrawCircle(Point center, float radius, float width, uint32_t color) = 0;
	virtual void FillCircle(Point center, float radius, uint32_t color) = 0;
};
