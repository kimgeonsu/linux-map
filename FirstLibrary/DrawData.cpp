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

void CDrawData::AddDataList(_MapRecord inData)
{
	std::cout << "AddDataList\n";
	std::list<_MapRecord>::iterator	listPos = _drawDataList.begin();
	std::list<_MapRecord>::iterator end = _drawDataList.end(); 
	//_MapRecord pData;
	bool isInsert = false;

	for (; listPos != end; listPos++) {
		//pData = *listPos;
		if (listPos->header.drawOrder > inData.header.drawOrder) {
			std::cout << "You? 1\n";
			_drawDataList.push_front(inData);
			isInsert = true;
			break;
		}
	}

	if (isInsert == false) {
			std::cout << "You? 2\n";
		_drawDataList.push_back(inData);
			std::cout << "You? 3\n";
	}
	return;
}