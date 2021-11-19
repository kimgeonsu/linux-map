#ifndef __FONT_H__
#define __FONT_H__

#include "type.h"

class Font
{
	public:
		Font(const WCHAR *family, double size);
		void SetFont(const WCHAR *family);
		void SetSize(double size);
};

#endif