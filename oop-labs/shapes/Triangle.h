#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Triangle : public ISolidShape
{
public:
	Triangle() = delete;
	Triangle(const Point& vertex1, const Point& vertex2, const Point& vertex3, uint32_t outlineColor, double outlineWidth, uint32_t fillColor);
	~Triangle() override = default;

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;
	[[nodiscard]] double GetOutlineWidth() const override;

	[[nodiscard]] Point GetVertex1() const;
	[[nodiscard]] Point GetVertex2() const;
	[[nodiscard]] Point GetVertex3() const;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
	double m_outlineWidth;
};
