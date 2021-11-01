// trytry.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "MapDataManager.h"
#include "MapDrawEngine.h"

using namespace std;

int main()
{
    std::cout << "Hello World!\n";

    std::string dataFilePath = "C:\\Users\\kundo\\Downloads\\PDU\\운용프로그램\\MapData\\Output";

    ////---------------------------------------------------
    CMapDrawEngine *engine = new CMapDrawEngine;

    engine->Init();
    engine->SetMapDataPath(dataFilePath);

    cout << engine->GetDeviceRect().left << endl;
    
    Graphics* graphics = new Graphics("dev/fb0");
    if (engine->DrawMap(graphics))
        cout << "I'm True hahahaha\n";

    return 0;
}