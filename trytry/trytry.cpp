// trytry.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "MapDataManager.h"
//#include "MapDrawEngine.h"

int main()
{
    std::cout << "Hello World!\n";

    std::string dataFilePath = "";

    MapDataManager mapMng;

    mapMng.Init();
    mapMng.setMapDataPath("C:\\Users\\kundo\\Downloads\\PDU\\운용프로그램\\MapData\\Output");
    mapMng.LoadMapData();
    std::cout << mapMng.GetMapDataPath();

    ////---------------------------------------------------
    //CMapDrawEngine engine;

    //engine.Init();
  
    return 0;
}