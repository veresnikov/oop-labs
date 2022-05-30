#pragma once
#include "IShape.h"
#include "Point.h"

class LineSegment : public IShape
{
public:
	LineSegment() = delete;
	LineSegment(const Point& startPosition, const Point& endPosition, uint32_t outlineColor, double outlineWidth);
	~LineSegment() override = default;

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] double GetOutlineWidth() const override;

	[[nodiscard]] Point GetStartPosition() const;
	[[nodiscard]] Point GetEndPosition() const;

private:
	Point m_startPosition;
	Point m_endPosition;
	uint32_t m_outlineColor;
	double m_outlineWidth;
};
