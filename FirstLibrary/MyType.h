#pragma once

#include "AppLibrary.h"
#include <string>
#include <cstring>

#include "./include/type.h"

typedef struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {};

	Point(int x_val, int y_val) : x(x_val), y(y_val){}

	Point(long x_val, long y_val) {
		x = x_val;
		y = y_val;
	}

	PointF Point2PointF() {
		PointF tmp;
		tmp.X = x;
		tmp.Y = y;

		return tmp;
	}
} Point;

typedef struct _dPoint {
	double x;
	double y;
} _dPoint;

typedef struct Rect {
	int top;
	int left;
	int bottom;
	int right;

	int Height() {
		return top - bottom;
	}

	int Width() {
		return right - left;
	}

	Rect() : top(0), left(0), bottom(0), right(0) {}
	Rect(int t, int l, int b, int r): top(t), left(l), bottom(b), right(r) {}

	Point TopLeft() {
		return Point(left, top);
	}

	Point CenterPoint() {
		return Point((left + right) / 2, (top + bottom) / 2);
	}

	void SetRect(int l, int t, int r, int b) {
		top = t;
		left = l;
		bottom = b;
		right = r;
	}

	bool PtInRect(Point p) {
		if (left <= p.x && top <= p.y && bottom >= p.y && p.x >= right) {
			return true;
		}
		return false;
	}
	bool IntersectRect(Rect* checkRect, Rect* objRect) {
		Rect min, max;
		if (checkRect->left <= objRect->left || checkRect->top <= objRect->top) {
			min = *checkRect;
			max = *objRect;
		}
		else {
			min = *objRect;
			max = *checkRect;
		}

		if (max.left > min.right && max.top >  min.bottom) {
			return false;
		}
		return true;
	}

	RectF Rect2RectF() {
		RectF tmp;
		tmp.X = left;
		tmp.Y = top;
		tmp.Height = bottom - top;
		tmp.Width = right - left;

		return tmp;
	}
} Rect;

typedef struct RectL {
	long top;
	long bottom;
	long left;
	long right;

	Rect RectL2Rect() {
		Rect tmp;
		tmp.left = left;
		tmp.right = right;
		tmp.top = top;
		tmp.bottom = bottom;

		return tmp;
	}
} RectL;

typedef struct PointL {
	long x;
	long y;
} PointL;

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
	RectL	boundaryRect;
	char			textLayerDes[32];
	char			textData[32];

	_MapRecordHeader() : designCode(0), objType(0), pointCount(0), drawOrder(0)
	{
		memset(&textData, 0, sizeof(textData));
		memset(&textLayerDes, 0, sizeof(textLayerDes));
	};

} _MapRecordHeader;

typedef struct _MapRecord
{
	_MapRecordHeader	header;
	Point* pointList;

	_MapRecord() : pointList(0) { };
	~_MapRecord()
	{
		
		GlReleaseMem(&pointList);
	}

	long getBuffer(unsigned int bufferSize)
	{
		// ������ ������ �޸� ����
		GlReleaseMem(&pointList);
		pointList = new Point[bufferSize];
		return true;
	}

	long releaseBuffer()
	{
		GlReleaseMem(&pointList);
		return true;
	}
} _MapRecord;

typedef struct _MapFactorInfo
{
	int			_baseLevelIdx;
	int			_levelIdxGap;
	int			_levelIdxCount;

	Point			_basePoint;
	int			_levelGapTable[2][16];
	double			_levelFactorTable[2][16];

	// 1/8 �� ������ ����
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
	long		physicalLevel;			// ������ ����
	long		logicalLevel;			// ������ ����
	long		mapAngle;
	long		headingUpMode;			// ����� ���
	long		dayNightMode;			// �߰� ���
	_dPoint		mapCenterPos;			// Map Center Point
	Point		mapCenterPos4096;		// Map Center Point 4096
	Rect		drawRect;				// 4096 RectF
	Rect		devRect;				// Device Full Size
	Point		devCenterPos;			// Device Center Point

	_MapDrawInfo() : physicalLevel(0), logicalLevel(0), mapAngle(0), headingUpMode(0),
		dayNightMode(0) {};
	~_MapDrawInfo() {};
} _MapDrawInfo;