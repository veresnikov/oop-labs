#include "Circle.h"

#include <cmath>
#include <iomanip>
#include <numbers>
#include <sstream>

Circle::Circle(const Point& center, double radius, uint32_t outlineColor, double outlineWidth, uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
	, m_outlineWidth(outlineWidth)
{
}

double Circle::GetArea() const
{
	return std::numbers::pi * std::pow(m_radius, 2);
}

double Circle::GetPerimeter() const
{
	return 2 * std::numbers::pi * m_radius;
}

std::string Circle::ToString() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << "circle " << m_center << " " << m_radius << " " << m_outlineColor << " " << m_outlineWidth << m_fillColor;
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

double Circle::GetOutlineWidth() const
{
	return m_outlineWidth;
}

Point Circle::GetCenter() const
{
	return m_center;
}

double Circle::GetRadius() const
{
	return m_radius;
}
