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
	//POSITION	listPos		= NULL;
	_MapRecord	*pData		= NULL;
	
	//listPos = _drawDataList.GetHeadPosition();
	
	/*while(listPos != NULL)
	{
		pData = (_MapRecord *)_drawDataList.GetNext(listPos);
		delete pData;
		pData = NULL;
	}*/
	
	//_drawDataList.RemoveAll();
	
	_level = 0;
	_parcelID.x = 0;
	_parcelID.y = 0;
	_parcelPos.x = 0;
	_parcelPos.y = 0;
}