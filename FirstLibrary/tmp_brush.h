#pragma once

#include "type.h"

class Brush
{
	Color c;
	float w;

public:
	Brush() : c(0, 0, 0), w(0) {};
	Brush(const Color& color, float width = 1.0f) {
		c = color;
		w = width;
	}
};