#ifndef __BRUSH_H__
#define __BRUSH_H__

#include "type.h"

class Brush
{
	public:
		Brush();
		Brush(const Color &color, REAL width = 1.0f);
};

#endif
