#pragma once
#include "ICanvasDrawable.h"
#include "ISolidShape.h"
#include "Point.h"

class Circle : public ISolidShape
{
public:
	Circle() = delete;
	Circle(const Point& center, float radius, uint32_t outlineColor, float outlineWidth, uint32_t fillColor);
	~Circle() override = default;

	[[nodiscard]] float GetArea() const override;
	[[nodiscard]] float GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;
	[[nodiscard]] float GetOutlineWidth() const override;

	void Draw(ICanvas& canvas) const override;

	[[nodiscard]] Point GetCenter() const;
	[[nodiscard]] float GetRadius() const;

private:
	Point m_center;
	float m_radius;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
	float m_outlineWidth;
};
