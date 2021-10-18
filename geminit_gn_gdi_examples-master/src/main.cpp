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
#include "font.h"
#include "brush.h"
#include "image.h"
#include "graphics.h"
}

Graphics 	*graphics;
Pen 		 pen;
Brush 		 brush;
Font 		 font;
Color 		 color;

void gn_gdi_init(void)
{
	graphics = new Graphics("/dev/fb0");
	pen 	 = Pen(color, 1.0);
	brush 	 = Brush(color);
	font 	 = Font("Sans_Regular_10.bdf", 10);
	color 	 = Color(0, 0, 0);
}

int main(int argc, char *argv[])
{
	gn_gdi_init();

	//점 그리기

	//선 그리기

	//삼각형 그리기

	//사각형 그리기

	//BMP, JPG, PNG 그리기
	Image bmp_image_red("images/bmp_test_red.bmp");
	Image jpg_image_red("images/jpg_test_red.jpg");
	Image png_image_red("images/png_test_red.png");
	Image bmp_image_green("images/bmp_test_green.bmp");
	Image jpg_image_green("images/jpg_test_green.jpg");
	Image png_image_green("images/png_test_green.png");
	Image bmp_image_blue("images/bmp_test_blue.bmp");
	Image jpg_image_blue("images/jpg_test_blue.jpg");
	Image png_image_blue("images/png_test_blue.png");
	g->DrawImage(&bmp_image_red, PointF(340, 110));
	g->DrawImage(&jpg_image_red, PointF(450, 110));
	g->DrawImage(&png_image_red, PointF(560, 110));
	g->DrawImage(&bmp_image_green, PointF(340, 220));
	g->DrawImage(&jpg_image_green, PointF(450, 220));
	g->DrawImage(&png_image_green, PointF(560, 220));
	g->DrawImage(&bmp_image_blue, PointF(340, 330));
	g->DrawImage(&jpg_image_blue, PointF(450, 330));
	g->DrawImage(&png_image_blue, PointF(560, 330));

	//지정 위치에 문자 및 숫자 표시
	WCHAR *str = "Geminit Hello! 1234567890";
	g->DrawString(str, -1, &font, PointF(10, 130), &brush);

	//문자, 숫자에 대한 폰트 및 크기 지정
	//font = Font("Arial", 30);
	//g->DrawString(str, -1, &font, PointF(10, 160), &brush);

	//선, 도형 두께 지정
	g->DrawLine(&p, PointF(10, 170), PointF(60, 170));
	g->DrawRectangle(&p, RectF(10, 180, 30, 30));

	//도형 내부 채우기
	g->FillRectangle(&brush, RectF(230, 10, 100, 100));

	//원 그리기
	g->DrawEllipse(&p, RectF(10, 220, 100, 100));
	g->FillEllipse(&brush, RectF(120, 220, 100, 100));

	//Polyline 그리기
	PointF points[6];
	PointF point;
	int i;
	int x = 10;
	int y = 430;
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
	g->DrawLines(&p, points, 5);

	//Polygon 그리기
	x = 120;
	y = 430;
	width = 100;
	height = 100;
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
	g->DrawPolygon(&p, points, 5);

	//////////////////////////////////////
	//파라미터 Excel에 있는 걸로 맞추기!!!!!
	//////////////////////////////////////

	graphics->~Graphics();

	return 0;
}
