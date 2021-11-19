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

Graphics 	*graphics;
Color 		 color(0, 0, 0);
Pen 		 pen(color, 1.0);

void polyline()
{
	PointF points[6];
	PointF point;
	int i;
	int x = 10;
	int y = 110;
	int width = 100;
	int height = 100;
	float rx;
	float ry;
	float cx;
	float cy;
	double theta;
	double dtheta;
	rx = ((x + width) - x) / 2;
	ry = (y - (y + height)) / 2;
	cx = x + rx;
	cy = y + ry;
	theta = (-M_PI) / 2;
	dtheta = (4 * M_PI) / 5;
	for (i = 0; i < 5; i++) {
		point.X = cx + (rx * cos(theta));
		point.Y = cy + (ry * sin(theta));
		points[i] = point;
		theta += dtheta;
	}

	graphics->DrawLines(&pen, points, 5);
}

void polygon()
{
	PointF points[6];
	PointF point;
	int i;
	int x = 120;
	int y = 110;
	int width = 100;
	int height = 100;
	float rx;
	float ry;
	float cx;
	float cy;
	double theta;
	double dtheta;
	rx = ((x + width) - x) / 2;
	ry = (y - (y + height)) / 2;
	cx = x + rx;
	cy = y + ry;
	theta = (-M_PI) / 2;
	dtheta = (4 * M_PI) / 5;
	for (i = 0; i < 5; i++) {
		point.X = cx + (rx * cos(theta));
		point.Y = cy + (ry * sin(theta));
		points[i] = point;
		theta += dtheta;
	}

	graphics->DrawPolygon(&pen, points, 5);
}

int main(int argc, char *argv[])
{
	graphics = new Graphics("/dev/fb0");

	//Screen clear.
	Brush clear(Color(255, 255, 255));
	graphics->FillRectangle(&clear, RectF(0, 0, 800, 480));
	//

	polyline();
	polygon();

	graphics->~Graphics();

	return 0;
}
