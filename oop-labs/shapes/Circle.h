#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Circle : public ISolidShape
{
public:
	Circle() = delete;
	Circle(const Point& center, double radius, uint32_t outlineColor, double outlineWidth, uint32_t fillColor);
	~Circle() override = default;

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;
	[[nodiscard]] double GetOutlineWidth() const override;

	[[nodiscard]] Point GetCenter() const;
	[[nodiscard]] double GetRadius() const;

private:
	Point m_center;
	double m_radius;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
	double m_outlineWidth;
};
