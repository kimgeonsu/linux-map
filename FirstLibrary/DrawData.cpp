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
	std::cout << "AddDataList\n";
	std::vector<_MapRecord>::iterator	listPos = _drawDataList.begin();
	std::vector<_MapRecord>::iterator   end = _drawDataList.end(); 
	_MapRecord* pData;
	bool isInsert = false;

	for (; listPos != end; listPos++) {
		if (listPos->header.drawOrder > inData->header.drawOrder) {
			std::cout << "You? 1\n";
			_drawDataList.insert(listPos-1, *inData);
			isInsert = true;
			break;
		}
	}
<<<<<<< HEAD
  
=======


>>>>>>> acd20a9d754f5ff2a5e7faacec6b93fb76afc383
	if (isInsert == false) {
			std::cout << "You? 2\n";
			std::cout << _drawDataList.size() << std::endl;
		_drawDataList.push_back(*inData);
			std::cout << "You? 3\n";
	}
	return;
}