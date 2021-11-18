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

int main(int argc, char *argv[])
{
	Graphics 	*graphics;
	Color 		 color(0, 0, 0);
	Brush 		 brush(color);
	Font 		 font("Sans-Regular", 10);

	graphics = new Graphics("/dev/fb0");
	
	Brush clear(Color(255, 255, 255));
	graphics->FillRectangle(&clear, RectF(0, 0, 800, 480));

	WCHAR *str = "Geminit Hello! 1234567890";
	graphics->DrawString(str, -1, &font, PointF(10, 10), &brush);

	graphics->~Graphics();

	return 0;
}
