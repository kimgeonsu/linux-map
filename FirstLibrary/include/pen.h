#ifndef __PEN_H__
#define __PEN_H__

#include "type.h"

#define PS_SOLID	0
#define PS_DASH		1	/* ------- */
#define PS_DOT		2	/* ....... */
#define PS_DASHDOT	3	/* _._._._ */
#define PS_DASHDOTDOT	4	/* _.._.._ */

class Pen
{
	public:
		Pen(const Color &color);
		Pen(const Color &color, REAL width);
		Pen(const Color &color, REAL width, INT dash_style);
		void SetColor(const Color &color);
		void SetAlpha(INT alpha);
		void SetWidth(REAL width);
		void SetDashStyle(INT dash_style);
};

#endif
