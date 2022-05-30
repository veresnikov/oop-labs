#pragma once
#include <string>

class IShape
{
public:
	[[nodiscard]] virtual double GetArea() const = 0;
	[[nodiscard]] virtual double GetPerimeter() const = 0;
	[[nodiscard]] virtual std::string ToString() const = 0;
	[[nodiscard]] virtual uint32_t GetOutlineColor() const = 0;
	[[nodiscard]] virtual double GetOutlineWidth() const = 0;

protected:
	virtual ~IShape() = default;
	IShape& operator=(const IShape&) = default;
};
