#ifndef __BRUSH_H__
#define __BRUSH_H__

#include "type.h"

class Brush
{
	public:
		Brush(const Color &color);
		void SetColor(const Color &_color);
		void SetAlpha(INT _alpha);
};

#endif
