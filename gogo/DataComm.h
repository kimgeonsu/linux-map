#pragma once
// DataComm.h: interface for the CDataComm class.
//
//////////////////////////////////////////////////////////////////////
#include "AppType.h"

namespace DATA_COMM_CONST
{
	const int		UDP_PORT = 5000;
	const int		CMD_PORT = 4000;
	const int		DTC_PORT = 3000;
}

class CDataComm
{
public:

	// Aircraft sta
	static int GetCurStaionByAircraftIndex(int index);
	static int GetAircraftIndex();

public:
	CDataComm();
	virtual ~CDataComm();

};
