#include "ShapesFactory.h"

std::shared_ptr<LineSegment> ShapesFactory::CreateLineSegment(const Point& startPosition, const Point& endPosition, uint32_t outlineColor, float outlineWidth)
{
	return std::make_shared<LineSegment>(startPosition, endPosition, outlineColor, outlineWidth);
}

std::shared_ptr<Rectangle> ShapesFactory::CreateRectangle(const Point& topLeft, const Point& bottomRight, uint32_t outlineColor, float outlineWidth, uint32_t fillColor)
{
	return std::make_shared<Rectangle>(topLeft, bottomRight, outlineColor, outlineWidth, fillColor);
}

std::shared_ptr<Triangle> ShapesFactory::CreateTriangle(const Point& vertex1, const Point& vertex2, const Point& vertex3, uint32_t outlineColor, float outlineWidth, uint32_t fillColor)
{
	return std::make_shared<Triangle>(vertex1, vertex2, vertex3, outlineColor, outlineWidth, fillColor);
}

std::shared_ptr<Circle> ShapesFactory::CreateCircle(const Point& center, float radius, uint32_t outlineColor, float outlineWidth, uint32_t fillColor)
{
	return std::make_shared<Circle>(center, radius, outlineColor, outlineWidth, fillColor);
}
