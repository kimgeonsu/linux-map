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
#include <sstream>
#include <cmath>
#include <vector>
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

int main()
{
    std::string dataFilePath = "../Output";
    CMapDrawEngine *engine = new CMapDrawEngine;
    engine->Init();
    engine->SetMapDataPath(dataFilePath);
	engine->SetDeviceRect(0, 0, 480, 800);
	engine->SetDeviceCenterPos(240, 400);

	engine->SetZoomLevel(0);
	engine->SetMapPos(128.0, 36.0);

	int currentAngle = 0;
	int currentMapMode = 1;
	engine->SetMapAngle(currentAngle);
	engine->SetMapHeadingUpMode(currentMapMode);
	engine->SetMapDayNightMode(0);

	_dPoint dp;
    dp.x = 128.5; 
    dp.y = 36.5;
    Point ip = Point(10,10);
    engine->WorldToDevice(dp);
    engine->DeviceToWorldMove(ip, ip);
    engine->DrawMap();

    string cmd;
	vector<string> commands;
	double data1, data2;
    while (1) {
        cout << "명령어를 입력하세용 : ";
		getline(cin, cmd);
		istringstream foo(cmd);
		string token;

		while(getline(foo, token, ' ')) {
			commands.push_back(token);
		}

		cout << cmd << endl;

        if (commands[0] == "move") {
			engine->MoveMap(stol(commands[1]), stol(commands[2]));
			engine->DrawMap();
        }
        if (commands[0] == "rotate") {
			engine->SetMapAngle(stol(commands[1]));
			engine->DrawMap();
		}
		if (commands[0] == "zoom") {
			engine->SetZoomLevel(stol(commands[1]));
			engine->DrawMap();
		}
		if (commands[0] == "dark") {
			engine->SetMapDayNightMode(0);
			engine->DrawMap();
		}
		if (commands[0] == "light") {
			engine->SetMapDayNightMode(1);
			engine->DrawMap();
		}
        if (commands[0] == "exit") {
			std::cout << "바이 바이 ~~~~\n";
            return 0;
        }
		commands.clear();
    }

// 	graphics = new Graphics("/dev/fb0");

// 	//Screen clear.
// 	Brush clear(Color(255, 255, 255));
// 	graphics->FillRectangle(&clear, RectF(0, 0, 800, 480));


// 	brush.SetColor(Color(255,127,39));

// 	PointF fox_pts[] = {

// // PointF(10 , -60),
// // PointF(20 , -40),
// // PointF(30 , -20),
// PointF(40 , -100),
// PointF(50 , 120),
// PointF(60 , 140),
// PointF(70 , 150),
// PointF(80 , 100),

// 	int cntPoint = sizeof fox_pts/sizeof fox_pts[0];
// 	std::cout << cntPoint << std::endl;

// 	graphics->FillPolygon(&brush, fox_pts, cntPoint);
// 	graphics->DrawPolygon(&pen, fox_pts, cntPoint);
// 	//

// 	graphics->~Graphics();


	return 0;
}
