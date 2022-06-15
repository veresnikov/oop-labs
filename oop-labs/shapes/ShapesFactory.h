#pragma once
#include "Circle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <memory>

class ShapesFactory
{
public:
	static std::shared_ptr<LineSegment> CreateLineSegment(const Point& startPosition, const Point& endPosition, uint32_t outlineColor, float outlineWidth);
	static std::shared_ptr<Rectangle> CreateRectangle(const Point& topLeft, const Point& bottomRight, uint32_t outlineColor, float outlineWidth, uint32_t fillColor);
	static std::shared_ptr<Triangle> CreateTriangle(const Point& vertex1, const Point& vertex2, const Point& vertex3, uint32_t outlineColor, float outlineWidth, uint32_t fillColor);
	static std::shared_ptr<Circle> CreateCircle(const Point& center, float radius, uint32_t outlineColor, float outlineWidth, uint32_t fillColor);
};
