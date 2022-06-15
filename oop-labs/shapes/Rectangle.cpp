#include "Rectangle.h"

#include <iomanip>
#include <sstream>

Rectangle::Rectangle(const Point& topLeft, const Point& bottomRight, const uint32_t outlineColor, const float outlineWidth, const uint32_t fillColor)
	: m_topLeft(topLeft)
	, m_bottomRight(bottomRight)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
	, m_outlineWidth(outlineWidth)
{
}

float Rectangle::GetArea() const
{
	return m_topLeft.GetLine({ m_bottomRight.x, m_topLeft.y }) * m_topLeft.GetLine({ m_topLeft.x, m_bottomRight.y });
}

float Rectangle::GetPerimeter() const
{
	return 2 * (m_topLeft.GetLine({ m_bottomRight.x, m_topLeft.y }) + m_topLeft.GetLine({ m_topLeft.x, m_bottomRight.y }));
}

std::string Rectangle::ToString() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << "rectangle " << m_topLeft << " " << m_bottomRight << " " << std::hex << m_outlineColor << " " << m_outlineWidth << " " << std::hex << m_fillColor;
	return ss.str();
}

uint32_t Rectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Rectangle::GetFillColor() const
{
	return m_fillColor;
}

float Rectangle::GetOutlineWidth() const
{
	return m_outlineWidth;
}

void Rectangle::Draw(ICanvas& canvas) const
{
	canvas.FillPolygon({ m_topLeft, { m_bottomRight.x, m_topLeft.y }, m_bottomRight, { m_topLeft.x, m_bottomRight.y } }, GetFillColor());
	canvas.DrawPolygon({ m_topLeft, { m_bottomRight.x, m_topLeft.y }, m_bottomRight, { m_topLeft.x, m_bottomRight.y } }, GetOutlineWidth(), GetOutlineColor());
}

Point Rectangle::GetTopLeft() const
{
	return m_topLeft;
}

Point Rectangle::GetBottomRight() const
{
	return m_bottomRight;
}
