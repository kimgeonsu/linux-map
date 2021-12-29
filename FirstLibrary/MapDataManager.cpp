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

long MapDataManager::ReadFile(std::string fileName)
{
	FILE* mapFile = nullptr;
	_MapRecord* pData = nullptr;

	mapFile = fopen((_mapDataPath + "/Lv1/0_0/" + fileName).c_str(), "r+b");
	if (mapFile != nullptr)
	{
		do
		{
			std::cout << "ho ho ho\n";
			pData = new _MapRecord();
			if (fread(&pData->header, sizeof(_MapRecordHeader), 1, mapFile) != 1)
			{
				fclose(mapFile);
				mapFile = nullptr;
				break;
			}

			std::cout << "ha ha ha\n";
			pData->pointList = new Point[pData->header.pointCount];
			if (fread(pData->pointList, sizeof(Point), pData->header.pointCount, mapFile) != (unsigned int)pData->header.pointCount)
			{
				fclose(mapFile);
				mapFile = nullptr;
				break;
			}
			_drawData.AddDataList(pData);

		} while (1);


		if (mapFile != nullptr)
			fclose(mapFile);
	}
	else {
		std::cout << "mapfile은 null임댱\n";
		return false;
	}

	return true;
}


