#pragma once

#include "type.h"

class Pen
{
public:
	Color c;
	float w;

	Pen() : c(0, 0, 0), w(0) {}
	Pen(const Color& color, float width = 1.0f) {}
};