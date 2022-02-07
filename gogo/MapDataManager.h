#pragma once
#pragma once

#include <iostream>
#include <string>
#include <list>
#include <dirent.h>

#include "MyType.h"
#include "DesignRecordManager.h"
#include "DrawData.h"


class MapDataManager {
public:
	MapDataManager();
	~MapDataManager();

private:
	std::string _mapDataPath;

public:
	long Init();
	long LoadMapData() {
		std::string searchPath;
		Point parcelID;
		std::string fileName;

		searchPath = _mapDataPath + "/Lv1/0_0";

		DIR* dir;
		struct dirent* ent;
		if ((dir = opendir(searchPath.c_str())) != nullptr) {
			while ((ent = readdir(dir)) != nullptr)
			{
				std::cout << ent->d_name << std::endl;
				ReadFile(ent->d_name);
				std:: cout << ent->d_name << " is completed!!\n";
			}
			closedir(dir);
		}
		else {
			perror("");
			return EXIT_FAILURE;
		}
		std::string designFileName;
		designFileName = _mapDataPath + "/Lv1_info.ddf";
		_designRecordMng.LoadDesignFile(designFileName);

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
	void SortAdd(_MapRecord* inData);
	long ReadFile(std::string fileName);

public:
	std::list<_MapRecord> _airMapList;
	CDrawData _drawData;
	CDesignRecordMng _designRecordMng;
};
