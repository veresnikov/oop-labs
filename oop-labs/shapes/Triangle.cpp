#include "Triangle.h"

#include <iomanip>
#include <sstream>

Triangle::Triangle(const Point& vertex1, const Point& vertex2, const Point& vertex3, const uint32_t outlineColor, const float outlineWidth, const uint32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
	, m_outlineWidth(outlineWidth)
{
}

float Triangle::GetArea() const
{
	return 0.5f * ((m_vertex1.x - m_vertex3.x) * (m_vertex2.y - m_vertex3.y) - (m_vertex1.y - m_vertex3.y) * (m_vertex2.x - m_vertex3.x));
}

float Triangle::GetPerimeter() const
{
	return m_vertex1.GetLine(m_vertex2) + m_vertex2.GetLine(m_vertex3) + m_vertex3.GetLine(m_vertex1);
}

std::string Triangle::ToString() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << "triangle " << m_vertex1 << " " << m_vertex2 << " " << m_vertex3 << " " << std::hex << m_outlineColor << " " << m_outlineWidth << " " << std::hex << m_fillColor;
	return ss.str();
}

uint32_t Triangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Triangle::GetFillColor() const
{
	return m_fillColor;
}

float Triangle::GetOutlineWidth() const
{
	return m_outlineWidth;
}

void Triangle::Draw(ICanvas& canvas) const
{
	canvas.FillPolygon({ GetVertex1(), GetVertex2(), GetVertex3() }, GetFillColor());
	canvas.DrawPolygon({ GetVertex1(), GetVertex2(), GetVertex3() }, GetOutlineWidth(), GetOutlineColor());
}

Point Triangle::GetVertex1() const
{
	return m_vertex1;
}

Point Triangle::GetVertex2() const
{
	return m_vertex2;
}

Point Triangle::GetVertex3() const
{
	return m_vertex3;
}
