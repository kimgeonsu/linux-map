#ifndef __PEN_H__
#define __PEN_H__

#include "type.h"

class Pen
{
	public:
		Pen(const Color &color, REAL width = 1.0f);
		void SetColor(const Color &_color);
		void SetWidth(REAL _width);
};

#endif