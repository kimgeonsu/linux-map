<<<<<<< HEAD:FirstLibrary/MapDesignRecordManager.h
=======
#include "Design.h"
#include "AppLibrary.h"

>>>>>>> parent of 6da7800 (왜 안될깡........):FirstLibrary/DesignRecordManager.h
#pragma once

#include <string>

class CMapDesignRecordMng
{
private:
	long			_recordCount;
	//_DesignRecord* _recordList;

public:
	long LoadDesignFile(std::string fileName);
	void Init()
	{
		_recordCount = 0;
		//GlReleaseMem(&_recordList);
	};
	long GetRecordCount()
	{
		return _recordCount;
	};
	//_DesignRecord* GetRecordData(long code)
	/*{
		if ((code < 0) || (code >= _recordCount) || (_recordList == NULL))
			return NULL;

		return &(_recordList[code]);
	};*/

public:
	CMapDesignRecordMng();
	virtual ~CMapDesignRecordMng();

};