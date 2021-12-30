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
#include <unistd.h>

extern "C" {
#include "./include/type.h"
#include "./include/pen.h"
#include "./include/brush.h"
#include "./include/graphics.h"
}

#include "MapDrawEngine.h"

using namespace std;

Graphics 	*graphics;
Color 		 color(0, 0, 0);
Pen 		 pen(color, 1.0);
Brush 		 brush(color);

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

void polygon(int px, int py, int pw, int ph)
{
	PointF points[6];
	PointF point;
	int i;
	int x = px;
	int y = py;
	int width = pw;
	int height = ph;
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

int main()
{
    // std::string dataFilePath = "../Output";
    // CMapDrawEngine *engine = new CMapDrawEngine;
    // engine->Init();
    // engine->SetMapDataPath(dataFilePath);
	// engine->SetDeviceRect(0, 0, 480, 800);
	// engine->SetDeviceCenterPos(240, 400);

	// engine->SetZoomLevel(0);
	// engine->SetMapPos(128.0, 36.0);

	// int currentAngle = 0;
	// int currentMapMode = 1;
	// engine->SetMapAngle(currentAngle);
	// engine->SetMapHeadingUpMode(currentMapMode);
    // engine->SetMapDayNightMode(1);

    // _dPoint dp;
    // dp.x = 128.5; 
    // dp.y = 36.5;
    // Point ip = Point(10,10);
    // engine->WorldToDevice(dp);
    // engine->DeviceToWorldMove(ip, ip);
    // engine->DrawMap();

    // string cmd;
    // while (1) {
    //     cout << ">";
    //     cin >> cmd;

    //     if (cmd == "move") {

    //     }
    //     if (cmd == "rotate") {

    //     }
    //     if (cmd == "zoom") {

    //     }
    //     if (cmd == "exit") {
    //         return 0;
    //     }

    // }
    
    graphics = new Graphics("/dev/fb0");

	//Screen clear.
	Brush clear(Color(255, 255, 255));
	graphics->FillRectangle(&clear, RectF(0, 0, 800, 480));
	//

	//star
	polyline();
	polygon(120, 110, 100, 100);
	//

	////hexagon
	int x = 10;
	int y = 120;

	PointF hexa_pts[] = {
		PointF(x+30, y), 
		PointF(x, y+50), 
		PointF(x+30, y+100), 
		PointF(x+80, y+100), 
		PointF(x+110, y+50), 
		PointF(x+80, y)
	};

	graphics->FillPolygon(&brush, hexa_pts, 6);
	graphics->DrawPolygon(&pen, hexa_pts, 6);
	//

	//triangle
	brush.SetColor(Color(0,255,0));
	pen.SetColor(Color(255,0,0));

	x = 200;
	y = 100;

	PointF triangle_pts[] = {PointF(x, y), PointF(x-100, y+200), PointF(x+50, y+20)};

	graphics->FillPolygon(&brush, triangle_pts, 3);
	graphics->DrawPolygon(&pen, triangle_pts, 3);

	pen.SetColor(Color(0,0,0));
	//

	//fox
	brush.SetColor(Color(255,127,39));

	x = 250;
	y = 120;

	PointF fox_pts[] = {
		PointF(x+30, y), 
		PointF(x, y+50), 
		PointF(x+55, y+100), 
		PointF(x+110, y+50), 
		PointF(x+80, y),
		PointF(x+70, y+25),
		PointF(x+40, y+25)
	};

	graphics->FillPolygon(&brush, fox_pts, 7);
	graphics->DrawPolygon(&pen, fox_pts, 7);
	//

	graphics->~Graphics();

	return 0;


}
