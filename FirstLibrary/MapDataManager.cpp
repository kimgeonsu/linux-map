#include "MapDataManager.h"

#define _CRT_SECURE_NO_WARNINGS


MapDataManager::MapDataManager()
{

}


MapDataManager::~MapDataManager()
{
	Init();
}

long MapDataManager::Init()
{
	_drawData.Init();
	_designRecordMng.Init();
	return true;
}

long MapDataManager::ReadFile(std::string fileName, CDrawData *drawData)
{
	FILE* mapFile = nullptr;
	_MapRecord* pData = nullptr;

	mapFile = fopen((_mapDataPath + "/Lv1/0_0/" + fileName).c_str(), "r+b");
	if (mapFile != nullptr)
	{
		do
		{
			std::cout << "Are you Problem? 1 \n";
			pData = new _MapRecord();
			if (fread(&pData->header, sizeof(_MapRecordHeader), 1, mapFile) != 1)
			{
				fclose(mapFile);
				mapFile = NULL;
				break;
			}
			std::cout << "Are you Problem? 2 \n";
			pData->pointList = new Point[pData->header.pointCount];
			if (fread(pData->pointList, sizeof(Point), pData->header.pointCount, mapFile) != (unsigned int)pData->header.pointCount)
			{
				fclose(mapFile);
				mapFile = NULL;
				break;
			}
			std::cout << "Are you Problem? 3 \n";
			drawData->AddDataList(pData);
			std::cout << "Are you Problem? 4 \n";

		} while (1);


		if (mapFile != NULL)
			fclose(mapFile);
	}
	else {
		return false;
	}

	return true;
}


