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
	FILE* mapFile = NULL;
	_MapRecord* pData = NULL;

	mapFile = fopen(fileName.c_str(), "r+b");
	if (mapFile != NULL)
	{
		std::cout << "설마 여기도??\n";
		do
		{
			pData = new _MapRecord();
			if (fread(&pData->header, sizeof(_MapRecordHeader), 1, mapFile) != 1)
			{
				fclose(mapFile);
				mapFile = NULL;
				break;
				std::cout << "멈춤 요인 1 \n";
			}

			pData->pointList = new Point[pData->header.pointCount];
			if (fread(pData->pointList, sizeof(Point), pData->header.pointCount, mapFile) != (unsigned int)pData->header.pointCount)
			{
				fclose(mapFile);
				mapFile = NULL;
				break;
				std::cout << "멈춤 요인 2 \n";
			}
			std::cout << "데이터 넣기" << std::endl;
			drawData->AddDataList(pData);

		} while (1);


		if (mapFile != NULL)
			fclose(mapFile);
	}
	else {
		std::cout << "퉤퉤퉤\n";
		return false;
	}

	return true;
}


