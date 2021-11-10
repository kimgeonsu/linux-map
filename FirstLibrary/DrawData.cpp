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
	_drawDataList.clear();
	_level = 0;
}

void CDrawData::AddDataList(_MapRecord* inData)
{
	std::list<_MapRecord>::iterator	listPos = _drawDataList.begin();
	std::list<_MapRecord>::iterator end = _drawDataList.end(); 

	bool isInsert = false;

	for (; listPos != end; listPos++) {
		if (listPos->header.drawOrder > inData->header.drawOrder) {
			_drawDataList.push_front(*inData);
			isInsert = true;
			break;
		}
	}

	if (isInsert == false) {
		_drawDataList.push_back(*inData);
	}
	return;
}