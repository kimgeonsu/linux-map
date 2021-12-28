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
    std::string dataFilePath = "../Output";
    CMapDrawEngine *engine = new CMapDrawEngine;
    engine->Init();
    engine->SetMapDataPath(dataFilePath);
	engine->SetDeviceRect(0, 0, 480, 800);
	engine->SetDeviceCenterPos(240, 400);

	engine->SetZoomLevel(0);
	engine->SetMapPos(128.0, 36.0);

	int currentAngle = 90;
	int currentMapMode = 1;
	engine->SetMapAngle(currentAngle);
	engine->SetMapHeadingUpMode(currentMapMode);
    engine->SetMapDayNightMode(1);

    _dPoint dp;
    dp.x = 128.5; 
    dp.y = 36.5;
    Point ip = Point(10,10);
    engine->WorldToDevice(dp);
    engine->DeviceToWorldMove(ip, ip);
    engine->DrawMap();

    // sleep(10);
    // std::cout << "MoveMap function executing...\n";
    // engine->MoveMap(10, 100);
    // engine->DrawMap();

    // sleep(10);
    // std::cout << "SetMapAngle function executing...\n";
    // engine->SetMapAngle(90);
    // engine->DrawMap();

    // sleep(10);
    // std::cout << "SetZoomLevel function executing...\n";
    // engine->SetZoomLevel(2);
    // engine->DrawMap();

    return 0;
}
