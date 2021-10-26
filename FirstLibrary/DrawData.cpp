#include "DrawData.h"
#include <list>
#include <iostream>

CDrawData::CDrawData() : _level(0)
{

}

CDrawData::~CDrawData()
{
	Init();
}

void CDrawData::Init()
{
	/*td::list<_MapRecord>::iterator listPos;
	_MapRecord pData; 

	listPos = _drawDataList.begin();

	while (listPos != _drawDataList.end())
	{
		pData = *listPos++;
		delete pData;
		pData = NULL;
	}*/

	_drawDataList.clear();

	_level = 0;
	_parcelID.x = 0;
	_parcelID.y = 0;
	_parcelPos.x = 0;
	_parcelPos.y = 0;
}

void CDrawData::AddDataList(_MapRecord* inData)
{
	std::list<_MapRecord>::iterator	listPos;
	std::list<_MapRecord>::iterator	oldListPos;
	_MapRecord pData;
	bool isInsert = false;


	for (listPos = _drawDataList.begin(); listPos != _drawDataList.end(); listPos++) {
		if (pData.header.drawOrder > inData->header.drawOrder) {
			_drawDataList.push_front(*inData);
			isInsert = true;
			break;
		}
	}

	if (isInsert == false)
		_drawDataList.push_back(*inData);
}