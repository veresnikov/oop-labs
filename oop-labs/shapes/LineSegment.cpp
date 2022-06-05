#include "LineSegment.h"

#include <iomanip>
#include <sstream>

LineSegment::LineSegment(const Point& startPosition, const Point& endPosition, const uint32_t outlineColor, const double outlineWidth)
	: m_startPosition(startPosition)
	, m_endPosition(endPosition)
	, m_outlineColor(outlineColor)
	, m_outlineWidth(outlineWidth)
{
}

double LineSegment::GetArea() const
{
	return GetPerimeter();
}

double LineSegment::GetPerimeter() const
{
	return m_startPosition.GetLine(m_endPosition);
}

std::string LineSegment::ToString() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << "line " << m_startPosition << " " << m_endPosition << " " << m_outlineColor << " " << m_outlineWidth;
	return ss.str();
}

uint32_t LineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

double LineSegment::GetOutlineWidth() const
{
	return m_outlineWidth;
}

Point LineSegment::GetStartPosition() const
{
	return m_startPosition;
}

Point LineSegment::GetEndPosition() const
{
	return m_endPosition;
}
