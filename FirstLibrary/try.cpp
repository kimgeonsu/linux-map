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

    Graphics 	*graphics;
	Color 		 color(255, 192, 0);
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
