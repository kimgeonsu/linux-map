#pragma once

#include "Design.h"
#include "AppLib.h"

#include <string>

class CDesignRecordMng
{
private:
	long			_recordCount;
	_DesignRecord* _recordList;

public:
	long LoadDesignFile(std::string fileName);
	void Init()
	{
		GlReleaseMem(&_recordList);
		_recordCount = 0;
	};
	long GetRecordCount()
	{
		return _recordCount;
	};
	_DesignRecord* GetRecordData(long code)
	{
		if ((code < 0) || (code >= _recordCount) || (_recordList == nullptr))
			return nullptr;

		return &(_recordList[code]);
	};


public:
	CDesignRecordMng();
	virtual ~CDesignRecordMng();

};