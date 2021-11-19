#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <iostream>
#include <fstream>
#include <cmath>

extern "C" {
#include "type.h"
#include "brush.h"
#include "font.h"
#include "graphics.h"
}

#define F8	8
#define F9	9
#define F10	10
#define F11	11
#define F12	12
#define F14	14
#define F16	16
#define F18	18
#define F20	20
#define F22	22
#define F24	24
#define F26	26

int main(int argc, char *argv[])
{
	Graphics 	*graphics;
	Color 		 color(0, 0, 0);
	Brush 		 brush(color);
	Font 		 font("Mono-Regular", F10);

	graphics = new Graphics("/dev/fb0");

	//Screen clear.
	Brush clear(Color(255, 255, 255));
	graphics->FillRectangle(&clear, RectF(0, 0, 800, 480));
	//

	WCHAR *str = "Geminit Hello! 1234567890";

	graphics->DrawString(str, -1, &font, PointF(10, 20), &brush);

	font.SetFont("Mono-Regular");
	font.SetSize(F20);
	graphics->DrawString(str, -1, &font, PointF(10, 50), &brush);

	font.SetFont("Sans-Regular");
	font.SetSize(F20);
	graphics->DrawString(str, -1, &font, PointF(10, 80), &brush);

	font.SetFont("Serif-Regular");
	font.SetSize(F20);
	graphics->DrawString(str, -1, &font, PointF(10, 110), &brush);

	graphics->~Graphics();

	return 0;
}
