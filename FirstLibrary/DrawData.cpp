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
	std::cout << "AddDataList 실행\n";
	//_MapRecord pData;
	bool isInsert = false;


	for (; listPos != end; listPos++) {
		//pData = *listPos;
		std::cout << "여기도 안되려나.......\n";
		std::cout << "drawOrder : " << inData->header.drawOrder << std::endl;
		if (listPos->header.drawOrder > inData->header.drawOrder) {
			_drawDataList.push_front(*inData);
			isInsert = true;
			break;
		}
	}

	if (isInsert == false)
		_drawDataList.push_back(*inData);

	return;
}