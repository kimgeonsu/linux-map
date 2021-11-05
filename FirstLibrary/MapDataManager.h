#pragma once

#include <iostream>
#include <string>
#include <list>
#include <iostream>
//#include <experimental/filesystem>
#include <dirent.h>
#include "MyType.h"
#include "DesignRecordManager.h"
#include "DrawData.h"

//namespace fs = std::experimental::filesystem;

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
	
		searchPath = _mapDataPath + "\\Lv1\\0_0";

		/*for (const fs::directory_entry& entry : fs::directory_iterator(searchPath)) {
			fileName = entry.path().string();
			ReadFile(fileName, &_drawData);
			std::cout << fileName << std::endl;
		}*/
		DIR* dir; 
		struct dirent* ent;
		if ((dir = opendir(searchPath.c_str())) != NULL) {
			while ((ent = readdir(dir)) != NULL)
			{	
				std::cout << ent->d_name << endl;
				ReadFile(ent->d_name, &_drawData);
			}
			closedir(dir);
		}
		else {
			perror("");
			return EXIT_FAILURE;
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
