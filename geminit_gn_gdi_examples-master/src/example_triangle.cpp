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
	Graphics *graphics;
	Color 	  color;
	Pen 	  pen;

	graphics = new Graphics("/dev/fb0");
	color 	 = Color(0, 0, 0);
	pen 	 = Pen(color, 1.0);

	PointF 	triangle[3];
	float 	x;
	float 	y;
	float 	width;
	float 	height;
	float 	h_center;

	x 	 = 10;
	y 	 = 10;
	width 	 = 100;
	height 	 = 100;

	h_center = x + (width / 2);

	triangle[0] = {h_center, y};
	triangle[1] = {x, y + width};
	triangle[2] = {x + width, y + height};

	graphics->DrawPolygon(&pen, triangle, 3);

	graphics->~Graphics();

	return 0;
}
