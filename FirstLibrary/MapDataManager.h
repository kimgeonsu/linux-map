#pragma once

#include <string>
#include <list>
#include "type.h"
#include "MapDataRecord.h"
#include "MapDesignRecordManager.h"

class MapDataManager {
public:
	MapDataManager();
	virtual ~MapDataManager();

private:
	std::string _mapDataPath;

public:
	long Init();
	long LoadMapData() {
		std::string searchPath;
		Point parcelID;
		std::string fileName;
		std::string csName;
		std::string csDirPath;

	//	CCeFileFind fia;

	//	csDirPath.Format(L"%s\\Lv%d\\%d_%d", _mapDataPath, 1, 0, 0);
	//	searchPath.Format(L"%s\\*.*", csDirPath);
		bool bFound;
	//	bFound = fia.FindFile(searchPath);

	//	while (bFound)
	//	{
	//		bFound = fia.FindNextFile();
	//		csName = fia.GetFileName();

	//		if (fia.IsDirectory())
	//		{
	//			//			GetSubFileList(strDir+csName);
	//		}
	//		else
	//		{
	//			if (csName.Find(L".rec") != -1 || csName.Find(L".REC") != -1)
	//			{
	//				fileName.Format(L"%s\\%s", csDirPath, csName);
	//				//					TRACE(L"%s\n", fileName);
	//				ReadFile(fileName, &_drawData);
	//			}

	//		}
	//	}

<<<<<<< HEAD
	//	fia.Close();
=======
		for (const fs::directory_entry& entry : fs::directory_iterator(searchPath)) {
			fileName = entry.path().string();
			ReadFile(fileName, &_drawData);
			/*std::cout << fileName << std::endl;*/
		}
>>>>>>> parent of 6da7800 (왜 안될깡........)

		std::string designFileName;
	//	designFileName.Format(L"%s\\Lv%d_info.ddf", _mapDataPath, 1);
	//	_designRecordMng.LoadDesignFile(designFileName);

		return true;
	}

	void setMapDataPath(std::string mapDataPath) {
		_mapDataPath = mapDataPath;
	}
	std::string GetMapDataPath() {
		return _mapDataPath;
	}

	void SaveAirMapData();
	void SelectAll();
	void ReleaseAll();
	void SortAdd(_MapRecord *inData);
	long ReadFile(std::string fileName, CMapDataRecord* drawData);

public :
	std::list<_MapRecord> _airMapList;
	CMapDataRecord _drawData;
	CMapDesignRecordMng _designRecorMng;
};
