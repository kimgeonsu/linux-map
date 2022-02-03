#pragma once
#include <string>

namespace APP_STATE_CONST
{
	const long CTRL_REDRAW_TIMER = 0x5100;
	const long CALI_RETRY_TIMER = 0x5101;
	const long RECV_ACK_COUNT_TIMER = 0x5102;
	const long SYNC_CLOCK_TIMER = 0x5103;
	const long DATA_TRANS_TIMER = 0x5104;
	const long TOUCH_BLOCK_TIMER = 0x5105;
	const long WAITING_DATA_TIMER = 0x5106;//110802 waiting channel time
	const long RDY_NEXT_TIMER = 0x5107;// READY NEXT Timer


	const long SEND_CLU_READY_TIMER = 0x5110;
	const long SEND_TAT_TIMER = 0x5111;
	const long SEND_MACH_TIMER = 0x5112;
	const long SEND_TOO_MSN_TIMER = 0x5113;
	const long SEND_BIT_TIMER = 0x5114;
	const long SEND_PP_MSN_TIMER = 0x5115;
	const long SEND_LOAD_MSN_TIMER = 0x5116;

	const long RECV_ACK_COUNT_INTERVAL = 10000;


	const long DATA_TRANS_INTERVAL = 2000;
	const long TOUCH_BLOCK_INTERVAL = 200;
	const long SEND_TIMER_INTERVAL = 1000;
	const long SEND_RETRY_COUNT = 10;

	const long LOG_INTERVAL = 10000;
	const long WAITING_DATA_INTERVAL = 30000;//110802

	// 20120115 : Lar Error (EUNG32)
	const double TBL_LAR_ALT_GAP = 1000.0;
	const double TBL_LAR_ALT = 20000.0;
	const long	 TBL_LAR_COUNT = 8;// org = 10; Modified by eung32
	//const double TBL_LAR_CHECK[10]		= {0.79, 0.78, 0.76, 0.75, 0.73, 0.72, 0.70, 0.69, 0.68, 0.66};
	const double TBL_LAR_CHECK[8] = { 0.79, 0.78, 0.76, 0.75, 0.73, 0.72, 0.70, 0.69 };

	// 20120115 : User layer Color Table
	// const long		TBL_WAY_COLOR_COUNT = 3;
	// const Color TBL_WAY_COLOR[3] = { Color(255, 250, 192, 144), Color(255, 74, 178, 100), Color(255,197, 216, 225) };

	namespace APP_MENU_MODE
	{
		const long LOGIN_MODE = 0;
		const long MAIN_MODE = 1;
		const long GPS_MODE = 2;
		const long USER_SETUP_MODE = 3;

		const long COUNT = 4;
	}

	namespace APP_MODE
	{
		const long GPS_BOMB = 0;
		const long SIMULATOR = 1;
		const long LOG = 2;
		const long CAS = 3;

		const long COUNT = 4;
	}

	namespace SCREEN_MODE
	{
		const long PIVOT_MODE = 0;
		const long REVERSE_MODE = 1;
		const long LANDSCAPE_MODE = 2;

		const long COUNT = 3;
	}

	namespace AIRCRAFT_TYPE
	{
		const long TYPE_F5 = 0;
		const long TYPE_F15S = 1;
		const long TYPE_F4 = 2;
		const long TYPE_F16 = 3;
		const long TYPE_FA50 = 4;

		const long COUNT = 5;
	}

	namespace SYMBOL_ID
	{
		const long AIR_BASE = 0;
		const long LAUNCH = 1;
		const long TARGET = 2;
		const long TOO_TARGET = 3;
		const long SCALE_BAR_1 = 4;
		const long SCALE_BAR_2 = 5;

		const long COUNT = 6;
	}

	namespace GPS_STATE
	{
		const long MODE_3D = 0;
		const long MODE_2D = 1;
		const long MODE_NOT_FIX = 2;
		const long MODE_INS = 3;

		const long COUNT = 4;
	}

	namespace BATTERY_STATE
	{
		const long FULL_STATE = 0;
		const long HIGH_STATE = 1;
		const long MIDDLE_STATE = 2;
		const long LOW_STATE = 3;
		const long CHARGE_STATE = 4;
		const long AC_STATE = 5;
	}

	namespace WEAPON_STATE
	{
		const long NO_WPN = 0;
		const long STBY_WPN = 1;
		const long WDEGD = 2;
		const long NO_WFAIL = 3;

		const long COUNT = 4;
	}


	namespace MESSAGE_CODE
	{
		const long NO_MIN_TGT = 0;
		const long TEST = 1;
		const long XFER = 2;
		const long NO_WFAIL = 3;
		const long WDEGD = 4;
		const long IN_RNG = 5;
		const long IN_ZONE = 6;
		const long LOW_BATT = 7;

		const long COUNT = 8;
	}

	namespace USER_SETUP_TYPE
	{
		namespace TIME_FORMAT
		{
			const long LOCAL_12 = 0;
			const long LOCAL_24 = 1;

			const long COUNT = 2;
		}

		namespace DATE_FORMAT
		{
			const long DD_MM_YY = 0;
			const long MM_DD_YY = 1;

			const long COUNT = 2;
		}

		namespace DISTANCE_UNITS
		{
			const long NM = 0;
			const long KM = 1;

			const long COUNT = 2;
		}

		namespace ALTITUDE_UNITS
		{
			const long FT = 0;
			const long MT = 1;

			const long COUNT = 2;
		}

		namespace SPEED_UNITS
		{
			const long KTS = 0;
			const long KPH = 1;
			const long MACH = 2;

			const long COUNT = 3;
		}

		namespace COORD_TYPE
		{
			const long DMS_DO = 0;
			const long DMS_MIN = 1;
			const long DMS_SEC = 2;

			const long COUNT = 3;
		}
	}

	namespace LOG_TYPE
	{
		const long ADD_KIT = 0;
		const long DEL_KIT = 1;
		const long CONNECTED_KIT = 2;
		const long CONNECTING_KIT = 3;
		const long CLOSE_KIT = 4;
		const long EVENT_MARK = 5;
		const long WIND_CHECK = 6;
		const long PP_MACH = 7;
		const long EDIT_MACH = 8;
		const long MAG_VAR_INPUT = 9;
		//20120312 eung32 added
		const long CONN_TIMEOUT = 10;
		const long MANUAL_CH_CHG = 11;
		const long CONN_TRY = 12;

		//const long COUNT			= 10; //modify by eung32 20120312
		const long COUNT = 13;

	}

	const wchar_t* const DISTANCE_UNITS_STRING[USER_SETUP_TYPE::DISTANCE_UNITS::COUNT] =
	{
		L"NM", L"Km"
	};

	const wchar_t* const ALTITUDE_UNITS_STRING[USER_SETUP_TYPE::ALTITUDE_UNITS::COUNT] =
	{
		L"ft", L"m"
	};

	const wchar_t* const SPEED_UNITS_STRING[USER_SETUP_TYPE::SPEED_UNITS::COUNT] =
	{
		L"KTS", L"KPH", L"M"
	};

	const wchar_t* const MONTH_STRING[12] =
	{
		L"JAN", L"FEB", L"MAR", L"APR",
		L"MAY", L"JUN", L"JUL", L"AUG",
		L"SEP", L"OCT", L"NOV", L"DEC"
	};

	const long STATION_ID[AIRCRAFT_TYPE::COUNT][4] =
	{
		{ 2, 3, 5, 6},
		{ 2, 0, 10, 8},
		{ 1, 2, 8, 9},
		{ 3, 4, 6, 7},
		//{ 3, 4, 6, 7}	 //org
		{ 2, 3, 5, 6}    //Modified by eung32 20120223
	};
}

typedef struct SAppState
{
	long	appMainMode;
	long	appMenuState;
	long	appDayNightMode;
	long	appScreenMode;
	long	appAircraftType;
	unsigned short	pduOP;
	unsigned short	pduBat;

	long	isDayNightModeChange;
	long	mapPanningMode;
	long	mapHeadingMode;
	long	appBatteryState;
	long	isOnUART;
	long	isIRLAR;
	long	isIZLAR;
	long	isLogPlayStart;
	long	isGPSThreadStart;
	long	isReadySelect;
	long	indexOfSelectStation;
	long	isHAEAltitude;
	long	isLogStart;
	long	isBitTest;				// is Try Bit Test
	long	isDataTrans;			// is Data Trans
	long	isDynmicLarTimeOut;
	long	isDynamicWind[4];
	long	netDevState;			// Device State
	long	isDynamicDebugText;

#if IS_DYNAMIC_LOG > 0
	long	isDisplayDynamicDebugMsg;
#endif

	long	isTouchBlock;
	short	rcvTAT;
	short	rcvMach;

	long	udpState;
	double	calcuTOF;
	double	homeDistance;
	double	dDynamicLarHeading;

#if defined(UNDER_CE)
	SYSTEM_POWER_STATUS_EX2 powerStatue;
#endif

	long				dynamicHeading;


	// Read �ÿ��� ��� ����.


	SAppState() : appMainMode(0), appMenuState(0), appDayNightMode(0), isOnUART(true), isBitTest(false), appScreenMode(0), appAircraftType(0), mapPanningMode(0), pduOP(0), pduBat(0), homeDistance(0.), dynamicHeading(0),
		mapHeadingMode(1), isDayNightModeChange(false), appBatteryState(0), isIRLAR(false), isIZLAR(false), indexOfSelectStation(0), isLogStart(false), isDataTrans(false), isTouchBlock(false),
		isLogPlayStart(false), isGPSThreadStart(false), isHAEAltitude(true), udpState(false), isDynmicLarTimeOut(false), isReadySelect(false), netDevState(true), isDynamicDebugText(false), calcuTOF(0.0), dDynamicLarHeading(0.0)
	{
		//		isGPSOK = false;

#if IS_DYNAMIC_LOG > 0
		isDisplayDynamicDebugMsg = false;
#endif

		rcvTAT = 0;
		rcvMach = 0;
		isDynamicWind[0] = false;
		isDynamicWind[1] = false;
		isDynamicWind[2] = false;
		isDynamicWind[3] = false;
	};
} SAppState;