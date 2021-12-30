#pragma once

#define _DEBUG

#include <string>

#include "MyType.h"
#include "MapDataManager.h"
#include "iCoord.h"

#include "./include/brush.h"
#include "./include/pen.h"
#include "./include/font.h"
#include "./include/graphics.h"
#include "./include/type.h"

class CMapDrawEngine
{
public:
	CMapDrawEngine();
	virtual ~CMapDrawEngine();

private:
	void SetPhysicalLevel(long level)
	{
		drawInfo.physicalLevel = level;
	};
	void GetPhysicalLevel(long& level)
	{
		level = drawInfo.physicalLevel;
	};
	long GetPhysicalLevel()
	{
		return drawInfo.physicalLevel;
	};

public:
	long Init();
	void SetMapDataPath(std::string mapDataPath)
	{
		mapDataManager.setMapDataPath(mapDataPath);
		mapDataManager.LoadMapData();
	};
	std::string GetMapDataPath()
	{
		return mapDataManager.GetMapDataPath();
	};
	void GetDeviceRect(Rect& RectF)						// Get Display Device Size
	{
		RectF = drawInfo.devRect;
	};
	Rect GetDeviceRect()
	{
		return drawInfo.devRect;
	};
	void SetDeviceRect(Rect RectF)
	{
		drawInfo.devRect = RectF;

		drawInfo.drawRect.left = 0;
		drawInfo.drawRect.top = 0;
		drawInfo.drawRect.right = (long)(4096. * RectF.right / 800.);
		drawInfo.drawRect.bottom = (long)(4096. * RectF.bottom / 800.);
	};
	void SetDeviceRect(long left, long top, long right, long bottom)
	{
		Rect tmpRect = Rect(left, top, right, bottom);
		SetDeviceRect(tmpRect);
	};

	void GetDeviceCenterPos(Point& pt)
	{
		pt = drawInfo.devCenterPos;
	};
	Point GetDeviceCenterPos()
	{
		return drawInfo.devCenterPos;
	};
	void SetDeviceCenterPos(Point pt)						// Map Center Point Mapping Device Center Point
	{
		drawInfo.devCenterPos = pt;
	};
	void SetDeviceCenterPos(long tx, long ty)				// Map Center Point Mapping Device Center Point
	{
		Point tmpPoint = Point(tx, ty);
		SetDeviceCenterPos(tmpPoint);
	};

	void SetZoomLevel(long level)							// Set Zoom Level
	{
		drawInfo.logicalLevel = level;
	};
	void GetZoomLevel(long& level)							// Get Zoom Level
	{
		level = drawInfo.logicalLevel;
	};
	long GetZoomLevel()
	{
		return drawInfo.logicalLevel;
	};

	void GetMapAngle(long& Angle)
	{
		Angle = 360 - drawInfo.mapAngle;
		if (Angle == 360)
			Angle = 0;
	};
	long GetMapAngle()
	{
		long retAngle = 0;
		retAngle = 360 - drawInfo.mapAngle;
		if (retAngle == 360)
			retAngle = 0;
		return retAngle;
	};
	void SetMapAngle(long Angle)
	{
		Angle %= 360;
		drawInfo.mapAngle = 360 - Angle;
		if (drawInfo.mapAngle == 360)
			drawInfo.mapAngle = 0;
	};

	void SetMapHeadingUpMode(long mode)
	{
		drawInfo.headingUpMode = mode;
	};
	void GetMapHeadingUpMode(long& mode)
	{
		mode = drawInfo.headingUpMode;
	};
	long GetMapHeadingUpMode()
	{
		return drawInfo.headingUpMode;
	};

	void SetMapDayNightMode(long mode)
	{
		drawInfo.dayNightMode = mode;
	}
	void GetMapDayNightMode(long& mode)
	{
		mode = drawInfo.dayNightMode;
	}
	long GetMapDayNightMode()
	{
		return drawInfo.dayNightMode;
	}

	void GetMapPos(_dPoint& pt)								// Get Current Map Point
	{
		pt.x = drawInfo.mapCenterPos.x / 28800.;
		pt.y = drawInfo.mapCenterPos.y / 28800.;
	};
	_dPoint GetMapPos()
	{
		_dPoint retPoint;
		GetMapPos(retPoint);
		return retPoint;
	};
	void GetMapPos(double& xPos, double& yPos)
	{
		xPos = drawInfo.mapCenterPos.x / 28800.;
		yPos = drawInfo.mapCenterPos.y / 28800.;
	};
	long SetMapPos(_dPoint pt)								// Move Map <Map Point>
	{
		SetMapPos(pt.x, pt.y);
		return true;
	};
	long SetMapPos(double xPos, double yPos)				// Move Map <Map Point>
	{
		drawInfo.mapCenterPos.x = xPos * 28800.;
		drawInfo.mapCenterPos.y = yPos * 28800.;

		Point	tmpPoint;
		long	level = _mapFactorInfo.GetTableLevel(0);
		long	xGap = _mapFactorInfo._levelGapTable[1][level];
		long	yGap = _mapFactorInfo._levelGapTable[0][level];

		tmpPoint.x = (long)drawInfo.mapCenterPos.x - _mapFactorInfo._basePoint.x;
		tmpPoint.y = (long)drawInfo.mapCenterPos.y - _mapFactorInfo._basePoint.y;

		drawInfo.mapCenterPos4096.x = tmpPoint.x * 4096 / xGap;
		drawInfo.mapCenterPos4096.y = tmpPoint.y * 4096 / yGap;
		return true;
	};

	long MoveMap(long dx, long dy)							// Move Map <Device Point>
	{
		Point	tmpPoint;
		tmpPoint.x = drawInfo.devCenterPos.x + dx;
		tmpPoint.y = drawInfo.devCenterPos.y + dy;

		drawInfo.mapCenterPos = DeviceToWorld(tmpPoint);
		return SetMapPos(drawInfo.mapCenterPos);;
	}
	long MoveMap(Point point, Point centerPoint)
	{
		Point		tmpPoint;

		if (drawInfo.headingUpMode == 1)
			tmpPoint = Rotate(point, centerPoint, GetMapAngle());
		else
			tmpPoint = point;

		drawInfo.mapCenterPos = DeviceToWorldMove(tmpPoint, centerPoint);
		return SetMapPos(drawInfo.mapCenterPos);
	}

	long DrawMap();					// Shape Data Draw
	long DrawPolygon( _MapRecord* pData, double angle, long bufferIdx);						// Polygon Draw
	long DrawPolyline(_MapRecord* pData, double angle, long bufferIdx);						// Polyline Draw
	long DrawPOI(_MapRecord* pData, double angle, long bufferIdx);							// POI Data Draw
	bool IsDrawObject(Rect drawRect, Rect objRect);

	Point Rotate(Point inPoint, Point centerPoint, long angle);
	Rect GetBoundaryRect(Rect inRect, long angle);

	Point WorldToDevice(const _dPoint _inPoint);
	_dPoint DeviceToWorld(const Point _inPoint);

	_dPoint DeviceToWorldMove(const Point _inPoint, Point centerPoint);

	long GetUTM(_dPoint inPoint, _dPoint& utmPoint, long param = 0);
	long GetUTM2KW(long izone, _dPoint utmPoint, KW& kw);

	std::string GetGP2MGRS(_dPoint inPoint);				
	std::string GetUTM2MGRS(int zone, _dPoint utmPoint);
	bool GetMGRS2KW(std::string mgrs, KW& kw);			
	bool GetMGRS2UTM(std::string mgrs, _dPoint& utmPoint);

	Color colorConverter(int data);

public:

	MapDataManager				mapDataManager;
	_MapFactorInfo			_mapFactorInfo;
	_MapDrawInfo			drawInfo;					// Draw Window Information

	Color					color = Color(0, 0, 0);
	Pen						m_NULLPEN = Pen(color, 1.0);
	Brush					m_NULLBRUSH = Brush(color);
	Brush					m_BACKBRUSH = Brush(color);
	Font					m_MapFont = Font("Sans-Regular", 10);

	long					m_CosValue[360];
	long					m_SinValue[360];
	CGeoCoordinate			m_Coordinate;			
	int						m_BaseZone;

	Graphics				*graphics;
};