#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Rectangle : public ISolidShape
{
public:
	Rectangle() = delete;
	Rectangle(const Point& topLeft, const Point& bottomRight, uint32_t outlineColor, double outlineWidth, uint32_t fillColor);
	~Rectangle() override = default;

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;
	[[nodiscard]] double GetOutlineWidth() const override;

	[[nodiscard]] Point GetTopLeft() const;
	[[nodiscard]] Point GetBottomRight() const;

private:
	Point m_topLeft;
	Point m_bottomRight;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
	double m_outlineWidth;
};
