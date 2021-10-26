#include "MapDataManager.h"
#include "DrawData.h"
#include "DrawData.cpp"

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
	FILE* mapFile = NULL;
	_MapRecord* pData = NULL;

	mapFile = fopen(fileName.c_str(), "r+b");
	if (mapFile != NULL)
	{
		do
		{
			pData = new _MapRecord();
			if (fread(&pData->header, sizeof(_MapRecordHeader), 1, mapFile) != 1)
			{
				fclose(mapFile);
				mapFile = NULL;
				break;
			}

			pData->pointList = new Point[pData->header.pointCount];
			if (fread(pData->pointList, sizeof(Point), pData->header.pointCount, mapFile) != (unsigned int)pData->header.pointCount)
			{
				fclose(mapFile);
				mapFile = NULL;
				break;
			}

			drawData->AddDataList(pData);

		} while (1);


		if (mapFile != NULL)
			fclose(mapFile);
	}
	else
		return false;

	return true;
}


