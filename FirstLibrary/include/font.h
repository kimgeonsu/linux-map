#ifndef __FONT_H__
#define __FONT_H__

#include "type.h"

class Font
{
	public:
		Font();
		Font(const WCHAR *family, double size);
};

#endif