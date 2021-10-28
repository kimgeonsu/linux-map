#pragma once

<<<<<<< HEAD
typedef struct Point {
	int x;
	int y;
} Point;

=======
#include "AppLibrary.h"
#include "Rect.h"
#include <string>

typedef struct Point {
	long x;
	long y;

	Point();

	Point(long x_val, long y_val) {
		x = x_val;
		y = y_val;
	}
} Point;

typedef struct _dPoint {
	double x;
	double y;
} _dPoint;


typedef struct LOGFONT {
	long      lfHeight;
	long      lfWidth;
	long      lfEscapement;
	long      lfOrientation;
	long      lfWeight;
	unsigned char      lfItalic;
	unsigned char      lfUnderline;
	unsigned char      lfStrikeOut;
	unsigned char      lfCharSet;
	unsigned char      lfOutPrecision;
	unsigned char      lfClipPrecision;
	unsigned char      lfQuality;
	unsigned char      lfPitchAndFamily;
	std::string     lfFaceName;
};


typedef union _MapCode
{
	char codeArray[8];
	int codeValue[2];

	_MapCode()
	{
		codeValue[1] = 0;
		codeValue[0] = 0;
	};

} _MapCode;

typedef struct _MapRecordHeader
{
	_MapCode objCode;
	int		designCode;
	int		objType;
	int		pointCount;
	int		drawOrder;
	Rect	boundaryRect;
	char			textLayerDes[32];
	char			textData[32];

	_MapRecordHeader() : designCode(0), objType(0), pointCount(0), drawOrder(0)
	{
		memset(&textData, 0, sizeof(textData));
		memset(&textLayerDes, 0, sizeof(textLayerDes));
	};

} _MapRecordHeader;

>>>>>>> parent of 6da7800 (ì™œ ì•ˆë ê¹¡........)
typedef struct _MapRecord
{
	//_MapRecordHeader	header;
	//_iPoint* pointList;

	//_MapRecord() : pointList(NULL) { };
	~_MapRecord()
	{
		//GlReleaseArray(&pointList);
	}

	long getBuffer(unsigned int bufferSize)
	{
		//GlReleaseArray(&pointList);
		//pointList = new _iPoint[bufferSize];
		return true;
	}

	long releaseBuffer()
	{
		//GlReleaseArray(&pointList);
		return true;
	}
<<<<<<< HEAD
} _MapRecord;
=======
} _MapRecord;

typedef struct _MapFactorInfo
{
	int			_baseLevelIdx;
	int			_levelIdxGap;
	int			_levelIdxCount;

	Point			_basePoint;
	int			_levelGapTable[2][16];
	double			_levelFactorTable[2][16];

	// 1/8 ÃÊ ´ÜÀ§·Î ÀúÀå
	_MapFactorInfo() : _basePoint(3456000, 940800), _baseLevelIdx(0), _levelIdxGap(2), _levelIdxCount(4)
	{
		for (unsigned int tblIndex = 0; tblIndex < 16; tblIndex++)
		{
			_levelGapTable[0][tblIndex] = 4800 << tblIndex;
			_levelGapTable[1][tblIndex] = 7200 << tblIndex;
			_levelFactorTable[0][tblIndex] = 4096. / (double)_levelGapTable[0][tblIndex];
			_levelFactorTable[1][tblIndex] = 4096. / (double)_levelGapTable[1][tblIndex];
		}
	}

	int GetTableLevel(int level)
	{
		return (_baseLevelIdx + ((_levelIdxCount - level - 1) * _levelIdxGap));
	}

	int GetInvertTableLevel(int level)
	{
		return (_baseLevelIdx + (level * _levelIdxGap));
	}

	int GetMapLevel(int level)
	{
		return (_levelIdxCount - (((level - _baseLevelIdx) / _levelIdxGap) + 1));
	}

	int GetXParcelCount(int level)
	{
		int retValue = 0;
		retValue = (int)(_levelGapTable[1][GetInvertTableLevel(level)] /
			_levelGapTable[1][_baseLevelIdx]);

		return retValue;
	};
	int GetYParcelCount(int level)
	{
		int retValue = 0;
		retValue = (int)(_levelGapTable[0][GetInvertTableLevel(level)] /
			_levelGapTable[0][_baseLevelIdx]);

		return retValue;
	};
	int GetMapMinX()
	{
		return _basePoint.x;
	};
	int GetMapMinY()
	{
		return _basePoint.y;
	};
	int GetMapMaxX()
	{
		return _basePoint.x + _levelGapTable[1][GetTableLevel(0)];
	};
	int GetMapMaxY()
	{
		return _basePoint.y + _levelGapTable[0][GetTableLevel(0)];;
	};

} _MapFactorInfo;


typedef struct _MapDrawInfo
{
	long		physicalLevel;			// ¹°¸®Àû ·¹º§
	long		logicalLevel;			// ³í¸®Àû ·¹º§
	long		mapAngle;
	long		headingUpMode;			// Çìµù¾÷ ¸ğµå
	long		dayNightMode;			// ¾ß°£ ¸ğµå
	_dPoint		mapCenterPos;			// Map Center Point
	Point		mapCenterPos4096;		// Map Center Point 4096
	Rect		drawRect;				// 4096 Rect
	Rect		devRect;				// Device Full Size
	Point		devCenterPos;			// Device Center Point

	_MapDrawInfo() : physicalLevel(0), logicalLevel(0), mapAngle(0), headingUpMode(0),
		dayNightMode(0) {};
	~_MapDrawInfo() {};
} _MapDrawInfo;
>>>>>>> parent of 6da7800 (ì™œ ì•ˆë ê¹¡........)
