#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>
#include <thread>


class Canvas : public ICanvas
{
public:
	Canvas(sf::RenderWindow& window);
	~Canvas() override;

	void DrawLine(Point start, Point end, float width, uint32_t color) override;
	void DrawPolygon(std::vector<Point> points, float width, uint32_t color) override;
	void FillPolygon(std::vector<Point> points, uint32_t color) override;
	void DrawCircle(Point center, float radius, float width, uint32_t color) override;
	void FillCircle(Point center, float radius, uint32_t color) override;

	static sf::Color GetColor(uint32_t color);

public:
	sf::RenderWindow& m_window;
};
