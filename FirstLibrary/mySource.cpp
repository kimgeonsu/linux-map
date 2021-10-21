#include "myHeader.h"

//DrawEngine::DrawEngine(IDataManager* dataMng) {
//	_dataManager = *dataMng;
//}

void DrawEngine::Init() {
	std::cout << "I'm Init Func!\n";
}

void DrawEngine::Release() {
	std::cout << "I'm Release Func!\n";
}

void DrawEngine::Draw() {
	std::cout << "I'm Draw Func!\n";
}

void DataManager::Init(std::string mapDataPath) {
	std::cout << "this is mapDataPath : " << mapDataPath << '\n';
}

void DataManager::Release() {
	std::cout << "I'm Release Func\n";
}