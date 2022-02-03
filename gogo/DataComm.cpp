// DataComm.cpp: implementation of the CDataComm class.
//
//////////////////////////////////////////////////////////////////////
#include "DataComm.h"
#include "AppType.h"

int StationNo[4][4] = { {2,3,5,6},
						{2,4,6,8},
						{1,2,8,9},
						{3,4,6,7} };

int CDataComm::GetCurStaionByAircraftIndex(int index)
{
	int return_value = 0;
	int idx = 0;

	if ((index >= 0) && (index < 4))
	{
		idx = GetAircraftIndex();
		return_value = StationNo[idx][index];
	}

	return return_value;
}

int CDataComm::GetAircraftIndex()
{
	int outindex = 0;
	// switch (GlAppState.appAircraftType)
	// {
	// case APP_STATE_CONST::AIRCRAFT_TYPE::TYPE_F5:
	// case APP_STATE_CONST::AIRCRAFT_TYPE::TYPE_FA50: //Modified by eung32 20120223
	// 	outindex = 0;
	// 	break;
	// case APP_STATE_CONST::AIRCRAFT_TYPE::TYPE_F15S:
	// 	outindex = 1;
	// 	break;
	// case APP_STATE_CONST::AIRCRAFT_TYPE::TYPE_F16:
	// 	//case APP_STATE_CONST::AIRCRAFT_TYPE::TYPE_FA50: //org
	// 	outindex = 3;
	// 	break;
	// case APP_STATE_CONST::AIRCRAFT_TYPE::TYPE_F4:
	// 	outindex = 2;
	// 	break;
	// default:
	// 	break;
	// }
	return outindex;
}