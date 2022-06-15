#pragma once
#include "ICanvasDrawable.h"
#include "ISolidShape.h"
#include "Point.h"

class Rectangle : public ISolidShape
{
public:
	Rectangle() = delete;
	Rectangle(const Point& topLeft, const Point& bottomRight, uint32_t outlineColor, float outlineWidth, uint32_t fillColor);
	~Rectangle() override = default;

	[[nodiscard]] float GetArea() const override;
	[[nodiscard]] float GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;
	[[nodiscard]] float GetOutlineWidth() const override;

	void Draw(ICanvas& canvas) const override;

	[[nodiscard]] Point GetTopLeft() const;
	[[nodiscard]] Point GetBottomRight() const;

private:
	Point m_topLeft;
	Point m_bottomRight;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
	float m_outlineWidth;
};
