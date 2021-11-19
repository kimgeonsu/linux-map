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
#include "image.h"
#include "graphics.h"
}

int main(int argc, char *argv[])
{
	Graphics *graphics;
	graphics = new Graphics("/dev/fb0");

	//Screen clear.
	Brush clear(Color(255, 255, 255));
	graphics->FillRectangle(&clear, RectF(0, 0, 800, 480));
	//

	Image bmp_image_red("images/bmp_test_red.bmp");
	Image bmp_image_green("images/bmp_test_green.bmp");
	Image bmp_image_blue("images/bmp_test_blue.bmp");

	Image jpg_image_red("images/jpg_test_red.jpg");
	Image jpg_image_green("images/jpg_test_green.jpg");
	Image jpg_image_blue("images/jpg_test_blue.jpg");

	Image png_image_red("images/png_test_red.png");
	Image png_image_green("images/png_test_green.png");
	Image png_image_blue("images/png_test_blue.png");

	graphics->DrawImage(&bmp_image_red, PointF(10, 10));
	graphics->DrawImage(&bmp_image_green, PointF(10, 120));
	graphics->DrawImage(&bmp_image_blue, PointF(10, 230));

	graphics->DrawImage(&jpg_image_red, PointF(120, 10));
	graphics->DrawImage(&jpg_image_green, PointF(120, 120));
	graphics->DrawImage(&jpg_image_blue, PointF(120, 230));

	graphics->DrawImage(&png_image_red, PointF(230, 10));
	graphics->DrawImage(&png_image_green, PointF(230, 120));
	graphics->DrawImage(&png_image_blue, PointF(230, 230));

	graphics->~Graphics();

	return 0;
}
