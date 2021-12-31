#include "DesignRecordManager.h"
#include <iostream>

#pragma warning(suppress : 4996)

CDesignRecordMng::CDesignRecordMng() : _recordCount(0), _recordList(nullptr)
{

}

CDesignRecordMng::~CDesignRecordMng() 
{
	GlReleaseMem(&_recordList);
}

long CDesignRecordMng::LoadDesignFile(std::string fileName)
{
	Init();

	FILE* pFile = nullptr;
	long	fileSize = 0;
	long	recIdx = 0;

	pFile = fopen(fileName.c_str(), "r+b");
	if (pFile == nullptr)
		return false;

	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	_recordCount = fileSize / sizeof(_DesignRecord);
	_recordList = new _DesignRecord[_recordCount];

	fread(&_recordList[recIdx], sizeof(_DesignRecord), _recordCount, pFile);


	fclose(pFile);

	for (int i = 0; i < _recordCount; i++) {
		if (_recordList[i].objType != 1)			
			std::cout << _recordList[i].designCode << " "<< std::hex << _recordList[i]._line[0].color << std::endl;
	}


	return true;
}