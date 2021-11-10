// trytry.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
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
#include "./include/type.h"
#include "./include/pen.h"
#include "./include/brush.h"
#include "./include/graphics.h"
}

#include "MapDrawEngine.h"

using namespace std;

int main()
{
    std::cout << "돌아와!\n";

    std::string dataFilePath = "../Output";

    ////---------------------------------------------------
    CMapDrawEngine *engine = new CMapDrawEngine;
    cout << "언 놈이 문제냐 1\n";
    engine->Init();
    cout << "언 놈이 문제냐 2\n";
    engine->SetMapDataPath(dataFilePath);
    cout << "언 놈이 문제냐 3\n";
	engine->SetDeviceRect(0, 0, 480, 800);
    cout << "언 놈이 문제냐 4\n";
	engine->SetDeviceCenterPos(240, 400);
    cout << "언 놈이 문제냐 5\n";
	engine->SetZoomLevel(0);
    cout << "언 놈이 문제냐 6\n";
	engine->SetMapPos(128.0, 36.0);
    cout << "언 놈이 문제냐 7\n";

	int currentAngle = 0;
	int currentMapMode = 0;
	engine->SetMapAngle(currentAngle);
    cout << "언 놈이 문제냐 8\n";
	engine->SetMapHeadingUpMode(currentMapMode);
    cout << "언 놈이 문제냐 9\n";
    
    // cout << engine->GetDeviceRect().left << endl;
    
    _dPoint dp;
    dp.x = 128.5;
    dp.y = 36.5;
    engine->WorldToDevice(dp);
    std::cout << "안녕~~\n";
    engine->DrawMap();
    
    return 0;
}
