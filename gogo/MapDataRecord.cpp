#include "MapDataRecord.h"

CMapDataRecord::CMapDataRecord() : _level(0)
{

}

CMapDataRecord::~CMapDataRecord()
{
	Init();
}

void CMapDataRecord::Init()
{
	_MapRecord* pData = nullptr;

	_level = 0;
	_parcelID.x = 0;
	_parcelID.y = 0;
	_parcelPos.x = 0;
	_parcelPos.y = 0;
}