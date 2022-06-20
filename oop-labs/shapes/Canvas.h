#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>
#include <thread>


class Canvas : public ICanvas
{
public:
	Canvas(sf::RenderWindow& window);
	~Canvas() override = default;

	void DrawLine(Point start, Point end, uint32_t color) override;
	void DrawPolygon(const std::vector<Point>& points, float width, uint32_t color) const override;
	void FillPolygon(const std::vector<Point>& points, uint32_t color) const override;
	void DrawCircle(Point center, float radius, float width, uint32_t color) override;
	void FillCircle(Point center, float radius, uint32_t color) override;

private:
	static sf::Color GetColor(uint32_t color);

	sf::RenderWindow& m_window;
};
