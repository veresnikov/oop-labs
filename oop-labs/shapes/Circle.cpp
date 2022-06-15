#include "Circle.h"

#include <cmath>
#include <iomanip>
#include <numbers>
#include <sstream>

Circle::Circle(const Point& center, const float radius, const uint32_t outlineColor, const float outlineWidth, const uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
	, m_outlineWidth(outlineWidth)
{
}

float Circle::GetArea() const
{
	return static_cast<float>(std::numbers::pi * std::pow(m_radius, 2));
}

float Circle::GetPerimeter() const
{
	return 2 * static_cast<float>(std::numbers::pi) * m_radius;
}

std::string Circle::ToString() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << "circle " << m_center << " " << m_radius << " " << std::hex << m_outlineColor << " " << m_outlineWidth << " " << std::hex << m_fillColor;
	return ss.str();
}

uint32_t Circle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Circle::GetFillColor() const
{
	return m_fillColor;
}

float Circle::GetOutlineWidth() const
{
	return m_outlineWidth;
}

void Circle::Draw(ICanvas& canvas) const
{
	canvas.FillCircle(GetCenter(), GetRadius(), GetFillColor());
	canvas.DrawCircle(GetCenter(), GetRadius(), GetOutlineWidth(), GetOutlineColor());
}

Point Circle::GetCenter() const
{
	return m_center;
}

float Circle::GetRadius() const
{
	return m_radius;
}
