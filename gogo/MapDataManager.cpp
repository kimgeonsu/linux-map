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
			pData = new _MapRecord();
			if (fread(&pData->header, sizeof(_MapRecordHeader), 1, mapFile) != 1)
			{
				fclose(mapFile);
				mapFile = nullptr;
				break;
			}

			pData->pointList = new Point[pData->header.pointCount];
			if (fread(pData->pointList, sizeof(Point), pData->header.pointCount, mapFile) != (unsigned int)pData->header.pointCount)
			{
				fclose(mapFile);
				mapFile = nullptr;
				break;
			}
			_drawData.AddDataList(pData);
			// _drawData.DebugPrint();
		} while (1);


		if (mapFile != nullptr)
			fclose(mapFile);
	}
	else {
		return false;
	}

	return true;
}

void MapDataManager::SaveAirMapData() {
	FILE* mapFile = nullptr;
	_MapRecord* pData = nullptr;

	std::string fileName = _mapDataPath + "/Lv1/0_0/SUAS.rec";
	mapFile = fopen(fileName.c_str(), "wb");

	if (mapFile != nullptr) {
		std::list<_MapRecord>::iterator listPos = _airMapList.begin();
		std::list<_MapRecord>::iterator end = _airMapList.end();

		for (; listPos != end; listPos++) {
			fwrite(&(listPos->header), sizeof(_MapRecordHeader), 1, mapFile);
			fwrite(&(listPos->pointList), sizeof(Point), listPos->header.pointCount, mapFile);
		}
		fclose(mapFile);
	}
}

void MapDataManager::SortAdd(_MapRecord* inData) {
	bool findFlag = false;

	std::list<_MapRecord>::iterator listPos = _airMapList.begin();
	std::list<_MapRecord>::iterator end = _airMapList.end();
	for (; listPos != end; listPos++) {
		if (strcmp(inData->header.textData, listPos->header.textData) < 0) {
			_airMapList.insert(listPos, *inData);
			findFlag = true;
			break;
		}
	}

	if (findFlag == false) {
		_airMapList.push_back(*inData);
	}
}

void MapDataManager::SelectAll() {
	std::list<_MapRecord>::iterator listPos = _airMapList.begin();
	std::list<_MapRecord>::iterator end = _airMapList.end();
	for (; listPos != end; listPos++) {
		listPos->header.isVisible = true;
	}
}

void MapDataManager::ReleaseAll() {
	std::list<_MapRecord>::iterator listPos = _airMapList.begin();
	std::list<_MapRecord>::iterator end = _airMapList.end();
	for (; listPos != end; listPos++) {
		listPos->header.isVisible = false;
	}
}
