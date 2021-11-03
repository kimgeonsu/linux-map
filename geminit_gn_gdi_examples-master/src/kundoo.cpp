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
#include "../lib/type.h"
#include "../lib/pen.h"
#include "../lib/brush.h"
#include "../lib/graphics.h"
}

int main(int argc, char *argv[])
{
	Graphics 	*graphics;
	Color 		 color;
	Pen 		 pen;
	Brush 		 brush;

	graphics = new Graphics("/dev/fb0");
	color 	 = Color(0, 0, 256);
	pen 	 = Pen(color, 1.0);
	brush 	 = Brush(color);

	graphics->DrawEllipse(&pen, RectF(10, 10, 100, 100));
	graphics->FillEllipse(&brush, RectF(120, 10, 100, 100));

	graphics->~Graphics();

	return 0;
}
