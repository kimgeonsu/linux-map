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
		if ((dir = opendir(searchPath.c_str())) != NULL) {
			while ((ent = readdir(dir)) != NULL)
			{	
				std::cout << ent->d_name << std::endl;
				ReadFile(ent->d_name, &_drawData);
			}
			closedir(dir);
		}
		else {
			perror("");
			std::cout << "I can't find.....TT\n";
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

	long ReadFile(std::string fileName);

public :
	CDrawData _drawData;
	CDesignRecordMng _designRecordMng;
};
