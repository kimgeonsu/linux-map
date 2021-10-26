#include <cstring>

#pragma once

#pragma pack(1)
// Structure Define
typedef union _ImageCode
{
	unsigned int data;
	struct
	{
		unsigned int yPos : 8;
		unsigned int xPos : 8;
		unsigned int Idx : 16;
	} Info;

	_ImageCode() :data(0)
	{
	};
	void initData()
	{
		data = 0;
	};
} _ImageCode;

typedef struct _PointInfo
{
	unsigned char PtType;
	unsigned char TxtPosition;
	unsigned int SymAngle;
	_ImageCode			SymCode;

	_PointInfo() : PtType(0), TxtPosition(0), SymAngle(0)
	{
	};
	void initData()
	{
		PtType = 0;
		TxtPosition = 0;
		SymAngle = 0;
		SymCode.initData();
	};
} _PointInfo;

typedef struct _LineInfo
{
	unsigned char type;
	unsigned char width;
	unsigned int color;

	_LineInfo() :type(0), width(0), color(0)
	{
	};
	void initData()
	{
		type = 0;
		width = 0;
		color = 0;
	};
} _LineInfo;

typedef struct _BrushInfo
{
	unsigned char type;
	_ImageCode fillValue;		// if Pattern ==> Pattern Index else if RGB ==> COLORREF

	_BrushInfo() :type(0)
	{
	};
	void initData()
	{
		type = 0;
		fillValue.initData();
	};
} _BrushInfo;

typedef struct _FontStyleRecord
{
	unsigned char size;
	unsigned char effect;
	unsigned int color;
	char fontName[64];			// Font Table

	_FontStyleRecord() :size(0), effect(0), color(0)
	{
		memset(fontName, 0, 64);
	};
	void initData()
	{
		size = 0;
		effect = 0;
		color = 0;
		memset(fontName, 0, 64);
	};
} _FontStyleRecord;

typedef struct _DesignRecord
{
	unsigned char useFlag;		// Project Using O:N, 1:U
	unsigned char visible;		// if visible(0) ==> Not Draw else Draw
	unsigned char objType;		// Point, Line, Polygon
	unsigned short order;			// Draw Order : 0x0000(First Draw), 0xffff(Last Draw)	
	unsigned int designCode;		// Design Code
	_PointInfo			_point[2];
	_LineInfo			_line[2];
	_BrushInfo			_brush[2];
	_FontStyleRecord	_fontStyle[2];		// Style Code <Font Information>

	_DesignRecord() :visible(0), order(0), designCode(0), objType(0), useFlag(0)
	{
	};
	void initData()
	{
		visible = 0;
		order = 0;
		designCode = 0;
		objType = 0;
		useFlag = 0;
		for (long idx = 0; idx < 2; idx++)
		{
			_point[idx].initData();
			_line[idx].initData();
			_brush[idx].initData();
			_fontStyle[idx].initData();
		}
	}
};
