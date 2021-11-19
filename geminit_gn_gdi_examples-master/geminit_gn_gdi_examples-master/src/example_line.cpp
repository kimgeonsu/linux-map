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
	Color 		 color(0, 0, 0);
	Pen 		 pen(color, 1.0);

	graphics = new Graphics("/dev/fb0");

	//Screen clear.
	Brush clear(Color(255, 255, 255));
	graphics->FillRectangle(&clear, RectF(0, 0, 800, 480));
	//

	graphics->DrawLine(&pen, PointF(10, 10), PointF(110, 10));
	graphics->DrawLine(&pen, PointF(110, 10), PointF(110, 110));
	graphics->DrawLine(&pen, PointF(110, 110), PointF(10, 110));
	graphics->DrawLine(&pen, PointF(10, 110), PointF(10, 10));

	pen.SetWidth(2.0);
	graphics->DrawLine(&pen, PointF(10+150, 10), PointF(110+150, 10));
	pen.SetWidth(3.0);
	graphics->DrawLine(&pen, PointF(110+150, 10), PointF(110+150, 110));
	pen.SetWidth(4.0);
	graphics->DrawLine(&pen, PointF(110+150, 110), PointF(10+150, 110));
	pen.SetWidth(5.0);
	graphics->DrawLine(&pen, PointF(10+150, 110), PointF(10+150, 10));

	pen.SetWidth(11.0);
	graphics->DrawLine(&pen, PointF(10, 200), PointF(10+100, 300));
	graphics->DrawLine(&pen, PointF(10+200+50, 300), PointF(10+100+50, 200));
	graphics->DrawLine(&pen, PointF(10+200+100, 300), PointF(10+300+100, 200));
	graphics->DrawLine(&pen, PointF(10+400+150, 200), PointF(10+300+150, 300));

	graphics->~Graphics();

	return 0;
}
