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
#include "pen.h"
#include "brush.h"
#include "graphics.h"
}

int main(int argc, char *argv[])
{
	Graphics 	*graphics;
	Color 		 color(0, 0, 0);
	Pen 		 pen(color, 1.0);
	Brush 		 brush(color);

	graphics = new Graphics("/dev/fb0");

	//Screen clear.
	Brush clear(Color(255, 255, 255));
	graphics->FillRectangle(&clear, RectF(0, 0, 800, 480));
	//

	graphics->DrawRectangle(&pen, RectF(10, 10, 100, 100));
	graphics->FillRectangle(&brush, RectF(120, 10, 100, 100));
	pen.SetWidth(10.0);
	graphics->DrawRectangle(&pen, RectF(10, 10+120, 100, 100));

	graphics->~Graphics();

	return 0;
}
