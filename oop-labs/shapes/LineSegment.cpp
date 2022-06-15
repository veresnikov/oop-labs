#include "LineSegment.h"
#include "ICanvas.h"
#include "ICanvasDrawable.h"

#include <iomanip>
#include <sstream>

LineSegment::LineSegment(const Point& startPosition, const Point& endPosition, const uint32_t outlineColor)
	: m_startPosition(startPosition)
	, m_endPosition(endPosition)
	, m_outlineColor(outlineColor)
{
}

float LineSegment::GetArea() const
{
	return GetPerimeter();
}

float LineSegment::GetPerimeter() const
{
	return m_startPosition.GetLine(m_endPosition);
}

std::string LineSegment::ToString() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << "line " << m_startPosition << " " << m_endPosition << " " << std::hex << m_outlineColor;
	return ss.str();
}

uint32_t LineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

float LineSegment::GetOutlineWidth() const
{
	return 1;
}

void LineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(GetStartPosition(), GetEndPosition(), GetOutlineColor());
}

Point LineSegment::GetStartPosition() const
{
	return m_startPosition;
}

Point LineSegment::GetEndPosition() const
{
	return m_endPosition;
}
