#include "DesignRecordManager.h"

#pragma warning(suppress : 4996)


CDesignRecordMng::CDesignRecordMng() : _recordCount(0), _recordList(NULL)
{

}

CDesignRecordMng::~CDesignRecordMng()
{
	GlReleaseMem(&_recordList);
}

long CDesignRecordMng::LoadDesignFile(std::string fileName)
{
	Init();

	FILE* pFile = NULL;
	long	fileSize = 0;
	long	recIdx = 0;

	pFile = fopen(fileName.c_str(), "r+b");
	if (pFile == NULL)
		return false;

	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	_recordCount = fileSize / sizeof(_DesignRecord);
	_recordList = new _DesignRecord[_recordCount];

	fread(&_recordList[recIdx], sizeof(_DesignRecord), _recordCount, pFile);

	//delete[] _recordList;
	fclose(pFile);

	return true;
}