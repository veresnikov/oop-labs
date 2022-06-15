#include "Canvas.h"

Canvas::Canvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void Canvas::DrawLine(Point start, Point end, uint32_t color)
{
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(start.x, start.y), GetColor(color)),
		sf::Vertex(sf::Vector2f(end.x, end.y), GetColor(color))
	};
	m_window.draw(std::ref(line), 2, sf::Lines);
}

void Canvas::DrawPolygon(std::vector<Point> points, float width, uint32_t color)
{
	sf::ConvexShape polygon(points.size());
	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}
	polygon.setOutlineThickness(width);
	polygon.setOutlineColor(GetColor(color));
	polygon.setFillColor(sf::Color::Transparent);
	m_window.draw(std::ref(polygon));
}

void Canvas::FillPolygon(std::vector<Point> points, uint32_t color)
{
	sf::ConvexShape polygon(points.size());
	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}
	polygon.setFillColor(GetColor(color));
	m_window.draw(std::ref(polygon));
}

void Canvas::DrawCircle(Point center, float radius, float width, uint32_t color)
{
	sf::CircleShape circle(radius);
	circle.setOutlineThickness(width);
	circle.setOutlineColor(GetColor(color));
	circle.setPosition(sf::Vector2f(center.x, center.y));
	m_window.draw(std::ref(circle));
}

void Canvas::FillCircle(Point center, float radius, uint32_t color)
{
	sf::CircleShape circle(radius);
	circle.setFillColor(GetColor(color));
	circle.setPosition(sf::Vector2f(center.x, center.y));
	m_window.draw(std::ref(circle));
}

sf::Color Canvas::GetColor(uint32_t color)
{
	uint8_t blue = color % 256;
	uint8_t green = (color / 256) % 256;
	uint8_t red = ((color / 256) / 256) % 256;

	return { red, green, blue };
}
