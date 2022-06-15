#pragma once
#include "ICanvasDrawable.h"
#include "IShape.h"
#include "Point.h"

class LineSegment : public IShape
{
public:
	LineSegment() = delete;
	LineSegment(const Point& startPosition, const Point& endPosition, uint32_t outlineColor, float outlineWidth);
	~LineSegment() override = default;

	[[nodiscard]] float GetArea() const override;
	[[nodiscard]] float GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] float GetOutlineWidth() const override;

	void Draw(ICanvas& canvas) const override;

	[[nodiscard]] Point GetStartPosition() const;
	[[nodiscard]] Point GetEndPosition() const;

private:
	Point m_startPosition;
	Point m_endPosition;
	uint32_t m_outlineColor;
	float m_outlineWidth;
};
