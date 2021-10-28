#pragma once

#include <string>
#include <iostream>

//class IDrawEngine {
//public:
//	virtual void Init() = 0;
//	virtual void Release() = 0;
//	virtual void Draw() = 0;
//};
//
//class IDataManager {
//public:
//	virtual void Init(std::string mapDataPath) = 0;
//	virtual void Release() = 0;
//};


class DrawEngine /*: public IDrawEngine*/ {
private:
	//IDataManager _dataManager;

public:
	//DrawEngine(IDataManager* dataMng);

	void Init();
	void Release();
	void Draw();
};

class DataManager /*: public IDataManager*/ {
public:
	void Init(std::string mapDataPath);
	void Release();
};


class CMapEngine {
private:
	DrawEngine* _drawEngine;
	DataManager* _dataManager;

public:
	CMapEngine(std::string dataFilePath) {
		_dataManager = new DataManager();
		_dataManager->Init(dataFilePath);
		//_drawEngine = new DrawEngine(*(_dataManager));
	}

	void Init() {
		return _drawEngine->Init();
	}
};


