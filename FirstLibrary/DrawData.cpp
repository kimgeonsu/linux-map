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
	std::cout << "사이즈 : "<< _drawDataList.size() << std::endl;
	if (listPos == end)
		std::cout << "we're same~~\n";
	for (; listPos != end; listPos++) {
		//pData = *listPos;
		if (listPos->header.drawOrder > inData->header.drawOrder) {
			_drawDataList.push_front(*inData);
			isInsert = true;
			break;
		}
	}

	if (isInsert == false) {
		std::cout <<"내가 다 문제야\n";
		_drawDataList.push_back(*inData);
	}
	return;
}