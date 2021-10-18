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
#include "graphics.h"
}

int main(int argc, char *argv[])
{
	Graphics 	*graphics;
	Color 		 color;
	Pen 		 pen;

	graphics = new Graphics("/dev/fb0");
	color 	 = Color(0, 0, 0);
	pen 	 = Pen(color, 1.0);

	graphics->DrawLine(&pen, PointF(10, 10), PointF(110, 10));
	graphics->DrawLine(&pen, PointF(110, 10), PointF(110, 110));
	graphics->DrawLine(&pen, PointF(110, 110), PointF(10, 110));
	graphics->DrawLine(&pen, PointF(10, 110), PointF(10, 10));

	graphics->~Graphics();

	return 0;
}
