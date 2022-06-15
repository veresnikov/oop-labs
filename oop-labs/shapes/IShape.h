#pragma once
#include <string>

class IShape : public ICanvasDrawable
{
public:
	[[nodiscard]] virtual float GetArea() const = 0;
	[[nodiscard]] virtual float GetPerimeter() const = 0;
	[[nodiscard]] virtual std::string ToString() const = 0;
	[[nodiscard]] virtual uint32_t GetOutlineColor() const = 0;
	[[nodiscard]] virtual float GetOutlineWidth() const = 0;

protected:
	virtual ~IShape() = default;
	IShape& operator=(const IShape&) = default;
};