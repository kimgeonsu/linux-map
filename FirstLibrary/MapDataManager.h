#pragma once

#include <iostream>
#include <string>
#include <list>
#include <format>
#include <iostream>
#include <filesystem>
#include "type.h"
#include "MapDataRecord.h"
#include "DesignRecordManager.h"
#include "DrawData.h"

namespace fs = std::filesystem;

class MapDataManager {
public:
	MapDataManager();
	~MapDataManager();

private:
	std::string _mapDataPath;

public:
	long Init();
	long LoadMapData() {
		long countIdx;
		std::string searchPath;
		Point parcelID;
		std::string fileName;
	
		searchPath = _mapDataPath + "\\Lv1\\0_0";

		for (const fs::directory_entry& entry : fs::directory_iterator(searchPath)) {
			fileName = entry.path().string();
			ReadFile(fileName, &_drawData);
			/*std::cout << fileName << std::endl;*/
		}

		std::string designFileName;
		designFileName = _mapDataPath + "\\Lv1_info.ddf";
		_designRecordMng.LoadDesignFile(designFileName);

		return true;
	}

	void setMapDataPath(std::string mapDataPath) {
		_mapDataPath = mapDataPath;
	}
	std::string GetMapDataPath() {
		return _mapDataPath;
	}

	long ReadFile(std::string fileName, CDrawData *drawData);

public :
	CDrawData _drawData;
	CDesignRecordMng _designRecordMng;
};
