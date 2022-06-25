#pragma once
#include "ShapesParser.h"

#include <mutex>

class ShapesController
{
public:

private:
	ShapesParser m_parser;
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::mutex m_mutex;
	std::thread m_windowThread;
};
