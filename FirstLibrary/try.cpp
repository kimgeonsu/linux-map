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
    std::cout << "Hello World!\n";

    std::string dataFilePath = "../Output";

    ////---------------------------------------------------
    CMapDrawEngine *engine = new CMapDrawEngine;

    engine->Init();
    engine->SetMapDataPath(dataFilePath);

    cout << engine->GetDeviceRect().left << endl;
    
    if (engine->  DrawMap())
        cout << "I'm True hahahaha\n";

    return 0;
}
