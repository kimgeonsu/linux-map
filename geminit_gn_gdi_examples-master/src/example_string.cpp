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
	Color 		 color;
	Brush 		 brush;
	Font 		 font("fonts/Sans-Regular_10.bdf", 10);

	graphics = new Graphics("/dev/fb0");
	color 	 = Color(0, 0, 0);
	brush 	 = Brush(color);

	WCHAR *str = "Geminit Hello! 1234567890";
	graphics->DrawString(str, -1, &font, PointF(10, 10), &brush);

	graphics->~Graphics();

	return 0;
}
