#pragma once
#pragma once

#define _DEBUG

#include <string>

#include "MyType.h"
#include "MapType.h"
#include "MapDataManager.h"
#include "iCoord.h"
#include "DataComm.h"
#include "AppLib.h"

#include "./include/brush.h"
#include "./include/pen.h"
#include "./include/font.h"
#include "./include/graphics.h"
#include "./include/type.h"

// class CMapDrawEngine
// {
// public:
// 	CMapDrawEngine();
// 	virtual ~CMapDrawEngine();

// private:
// 	void SetPhysicalLevel(long level)
// 	{
// 		drawInfo.physicalLevel = level;
// 	};
// 	void GetPhysicalLevel(long& level)
// 	{
// 		level = drawInfo.physicalLevel;
// 	};
// 	long GetPhysicalLevel()
// 	{
// 		return drawInfo.physicalLevel;
// 	};

// public:	
// 	long Init();
// 	void SetMapDataPath(std::string mapDataPath)
// 	{
// 		mapDataManager.setMapDataPath(mapDataPath);
// 		mapDataManager.LoadMapData();
// 	};
// 	std::string GetMapDataPath()
// 	{
// 		return mapDataManager.GetMapDataPath();
// 	};
// 	void GetDeviceRect(Rect& RectF)						// Get Display Device Size
// 	{
// 		RectF = drawInfo.devRect;
// 	};
// 	Rect GetDeviceRect()
// 	{
// 		return drawInfo.devRect;
// 	};
// 	void SetDeviceRect(Rect RectF)
// 	{
// 		drawInfo.devRect = RectF;

// 		drawInfo.drawRect.left = 0;
// 		drawInfo.drawRect.top = 0;
// 		drawInfo.drawRect.right = (long)(4096. * RectF.right / 800.);
// 		drawInfo.drawRect.bottom = (long)(4096. * RectF.bottom / 800.);
// 	};
// 	void SetDeviceRect(long left, long top, long right, long bottom)
// 	{
// 		Rect tmpRect = Rect(left, top, right, bottom);
// 		SetDeviceRect(tmpRect);
// 	};

// 	void GetDeviceCenterPos(Point& pt)
// 	{
// 		pt = drawInfo.devCenterPos;
// 	};
// 	Point GetDeviceCenterPos()
// 	{
// 		return drawInfo.devCenterPos;
// 	};
// 	void SetDeviceCenterPos(Point pt)						// Map Center Point Mapping Device Center Point
// 	{
// 		drawInfo.devCenterPos = pt;
// 	};
// 	void SetDeviceCenterPos(long tx, long ty)				// Map Center Point Mapping Device Center Point
// 	{
// 		Point tmpPoint = Point(tx, ty);
// 		SetDeviceCenterPos(tmpPoint);
// 	};

// 	void SetZoomLevel(long level)							// Set Zoom Level
// 	{
// 		debugIndex = 0;
// 		drawInfo.logicalLevel = level;
// 	};
// 	void GetZoomLevel(long& level)							// Get Zoom Level
// 	{
// 		level = drawInfo.logicalLevel;
// 	};
// 	long GetZoomLevel()
// 	{
// 		return drawInfo.logicalLevel;
// 	};

// 	void GetMapAngle(long& Angle)
// 	{
// 		Angle = 360 - drawInfo.mapAngle;
// 		if (Angle == 360)
// 			Angle = 0;
// 	};
// 	long GetMapAngle()
// 	{
// 		long retAngle = 0;
// 		retAngle = 360 - drawInfo.mapAngle;
// 		if (retAngle == 360)
// 			retAngle = 0;
// 		return retAngle;
// 	};
// 	void SetMapAngle(long Angle)
// 	{
// 		Angle %= 360;
// 		drawInfo.mapAngle = 360 - Angle;
// 		if (drawInfo.mapAngle == 360)
// 			drawInfo.mapAngle = 0;
// 	};

// 	void SetMapHeadingUpMode(long mode)
// 	{
// 		drawInfo.headingUpMode = mode;
// 	};
// 	void GetMapHeadingUpMode(long& mode)
// 	{
// 		mode = drawInfo.headingUpMode;
// 	};
// 	long GetMapHeadingUpMode()
// 	{
// 		return drawInfo.headingUpMode;
// 	};

// 	void SetMapDayNightMode(long mode)
// 	{
// 		drawInfo.dayNightMode = mode;
// 	}
// 	void GetMapDayNightMode(long& mode)
// 	{
// 		mode = drawInfo.dayNightMode;
// 	}
// 	long GetMapDayNightMode()
// 	{
// 		return drawInfo.dayNightMode;
// 	}

// 	void GetMapPos(_dPoint& pt)								// Get Current Map Point
// 	{
// 		pt.x = drawInfo.mapCenterPos.x / 28800.;
// 		pt.y = drawInfo.mapCenterPos.y / 28800.;
// 	};
// 	_dPoint GetMapPos()
// 	{
// 		_dPoint retPoint;
// 		GetMapPos(retPoint);
// 		return retPoint;
// 	};
// 	void GetMapPos(double& xPos, double& yPos)
// 	{
// 		xPos = drawInfo.mapCenterPos.x / 28800.;
// 		yPos = drawInfo.mapCenterPos.y / 28800.;
// 	};
// 	long SetMapPos(_dPoint pt)								// Move Map <Map Point>
// 	{
// 		SetMapPos(pt.x, pt.y);
// 		return true;
// 	};
// 	long SetMapPos(double xPos, double yPos)				// Move Map <Map Point>
// 	{
// 		drawInfo.mapCenterPos.x = xPos * 28800.;
// 		drawInfo.mapCenterPos.y = yPos * 28800.;

// 		Point	tmpPoint;
// 		long	level = _mapFactorInfo.GetTableLevel(0);
// 		long	xGap = _mapFactorInfo._levelGapTable[1][level];
// 		long	yGap = _mapFactorInfo._levelGapTable[0][level];

// 		tmpPoint.x = (long)drawInfo.mapCenterPos.x - _mapFactorInfo._basePoint.x;
// 		tmpPoint.y = (long)drawInfo.mapCenterPos.y - _mapFactorInfo._basePoint.y;

// 		drawInfo.mapCenterPos4096.x = tmpPoint.x * 4096 / xGap;
// 		drawInfo.mapCenterPos4096.y = tmpPoint.y * 4096 / yGap;
// 		return true;
// 	};

// 	long MoveMap(long dx, long dy)							// Move Map <Device Point>
// 	{
// 		Point	tmpPoint;
// 		tmpPoint.x = drawInfo.devCenterPos.x + dx;
// 		tmpPoint.y = drawInfo.devCenterPos.y + dy;

// 		drawInfo.mapCenterPos = DeviceToWorld(tmpPoint);
// 		return SetMapPos(drawInfo.mapCenterPos);;
// 	}
// 	long MoveMap(Point point, Point centerPoint)
// 	{
// 		Point		tmpPoint;

// 		if (drawInfo.headingUpMode == 1)
// 			tmpPoint = Rotate(point, centerPoint, GetMapAngle());
// 		else
// 			tmpPoint = point;

// 		drawInfo.mapCenterPos = DeviceToWorldMove(tmpPoint, centerPoint);
// 		return SetMapPos(drawInfo.mapCenterPos);
// 	}

// 	long DrawMap();					// Shape Data Draw
// 	long DrawPolygon( _MapRecord* pData, double angle, long bufferIdx);						// Polygon Draw
// 	long DrawPolyline(_MapRecord* pData, double angle, long bufferIdx);						// Polyline Draw
// 	long DrawPOI(_MapRecord* pData, double angle, long bufferIdx);							// POI Data Draw
// 	bool IsDrawObject(Rect drawRect, Rect objRect);

// 	Point Rotate(Point inPoint, Point centerPoint, long angle);
// 	Rect GetBoundaryRect(Rect inRect, long angle);

// 	Point WorldToDevice(const _dPoint _inPoint);
// 	_dPoint DeviceToWorld(const Point _inPoint);

// 	_dPoint DeviceToWorldMove(const Point _inPoint, Point centerPoint);

// 	long GetUTM(_dPoint inPoint, _dPoint& utmPoint, long param = 0);
// 	long GetUTM2KW(long izone, _dPoint utmPoint, KW& kw);

// 	std::string GetGP2MGRS(_dPoint inPoint);				
// 	std::string GetUTM2MGRS(int zone, _dPoint utmPoint);
// 	bool GetMGRS2KW(std::string mgrs, KW& kw);			
// 	bool GetMGRS2UTM(std::string mgrs, _dPoint& utmPoint);

// 	Color colorConverter(int data);

// public:

// 	MapDataManager				mapDataManager;
// 	_MapFactorInfo			_mapFactorInfo;
// 	_MapDrawInfo			drawInfo;					// Draw Wiundow Information

// 	Color					color = Color(0, 0, 0);
// 	Pen						m_NULLPEN = Pen(color, 1.0);
// 	Brush					m_NULLBRUSH = Brush(color);
// 	Brush					m_BACKBRUSH = Brush(color);
// 	Font					m_MapFont = Font("Sans-Regular", 10);

// 	long					m_CosValue[360];
// 	long					m_SinValue[360];
// 	CGeoCoordinate			m_Coordinate;			
// 	int						m_BaseZone;

// 	Graphics				*graphics;

// 	int 					debugIndex;
// };

namespace MAP_DRAW_ENGINE_CONST
{
	namespace SYMBOL_TYPE
	{
		const long AIR_BASE = 0;
		const long LAUNCH = 1;
		const long TARGET = 2;
		const long KM_SCALE_BAR = 3;
		const long NM_SCALE_BAR = 4;

		const long COUNT = 5;
	}
	const long	AngleBoxStartX = 195;
	const long	AngleBoxStartY = 246;
	const Rect AngleBoxArea = Rect(0, 0, 90, 40);

	const Point SCALE_BAR_POS = Point(55, 295);

	const long SYMBOL_POINT_COUNT[SYMBOL_TYPE::COUNT] = { 6, 6, 4, 4, 4 };
	const Point SYMBOL_SIZE[SYMBOL_TYPE::COUNT] =
	{
		Point(30, 30), Point(50, 50), Point(50, 50),
		Point(20, 106), Point(20, 98)
	};
	const Point SYMBOL_DATA[SYMBOL_TYPE::COUNT][8] =
	{
		{
			Point(3, 3), Point(27, 3), Point(27, 20), Point(15, 27), Point(3, 20),
			Point(3, 3), Point(0, 0), Point(0, 0)
		},
		{
			Point(25, 18), Point(33, 23), Point(29, 32), Point(21, 32), Point(18, 23),
			Point(25, 18), Point(25, 0), Point(0, 0)
		},
		{
			Point(25, 15), Point(39, 35), Point(11, 35), Point(25, 15), Point(25, 0),
			Point(0, 0), Point(0, 0), Point(0, 0)
		},
		{
			Point(0, 0), Point(20, 0), Point(20, 106), Point(0, 106), Point(0, 0),
			Point(0, 0), Point(0, 0), Point(0, 0)
		},
		{
			Point(0, 0), Point(20, 0), Point(20, 86), Point(0, 86), Point(0, 0),
			Point(0, 0), Point(0, 0), Point(0, 0)
		}
	};
}

class CMapDrawEngine
{
public:
	CMapDrawEngine();
	virtual ~CMapDrawEngine();

private:
	long LongMultiDouble(long inValue, double factor)
	{
		double	tmpValue = inValue * factor;
		return (long)tmpValue;
	};

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
	void GetDeviceRect(Rect& rect)						// Get Display Device Size
	{
		rect = drawInfo.devRect;
	};
	Rect GetDeviceRect()
	{
		return drawInfo.devRect;
	};
	void SetDeviceRect(Rect rect)
	{
		drawInfo.devRect = rect;

		drawInfo.drawRect.left = 0;
		drawInfo.drawRect.top = 0;
		drawInfo.drawRect.right = (long)(4096. * rect.right / 800.);
		drawInfo.drawRect.bottom = (long)(4096. * rect.bottom / 600.);
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
	long SetMapPosUTM(_dPoint pt)
	{
		_LatLonDMS latlonDMS;
		_dPoint calcuPoint;
		GetUTM2KW(40, pt, latlonDMS);
		CAppLib::Coord_GetDegreebyDMS(latlonDMS, calcuPoint);

		return SetMapPos(calcuPoint);
	}
	long SetMapPosUTM(double xPos, double yPos)
	{
		_dPoint tmpPoint;
		tmpPoint.x = xPos;
		tmpPoint.y = yPos;
		return SetMapPosUTM(tmpPoint);
	}
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
		long	xGap = _mapFactorInfo._levelGapTable[GREEN_MAP_CONST::MAP_POSITION_INDEX::LONGITUDE][level];
		long	yGap = _mapFactorInfo._levelGapTable[GREEN_MAP_CONST::MAP_POSITION_INDEX::LATITUDE][level];

		tmpPoint.x = (long)drawInfo.mapCenterPos.x - _mapFactorInfo._basePoint.x;
		tmpPoint.y = (long)drawInfo.mapCenterPos.y - _mapFactorInfo._basePoint.y;

		drawInfo.mapCenterPos4096.x = tmpPoint.x * 4096 / xGap;
		drawInfo.mapCenterPos4096.y = tmpPoint.y * 4096 / yGap;
		return true;
	};
	long SetCarPos(_dPoint pt)
	{
		return SetCarPos(pt.x, pt.y);
	}
	long SetCarPos(double xPos, double yPos)
	{
		carPos.x = xPos;
		carPos.y = yPos;
		return true;
	}

	long MoveMap(long dx, long dy)							// Move Map <Device Point>
	{
		Point	tmpPoint;
		_dPoint	tmpMapPoint;

		tmpPoint.x = drawInfo.devCenterPos.x + dx;
		tmpPoint.y = drawInfo.devCenterPos.y + dy;

		tmpMapPoint = DeviceToWorld(tmpPoint);
		if ((tmpMapPoint.x < 36) || (tmpMapPoint.x > 60) || (tmpMapPoint.y < 8) || (tmpMapPoint.y > 32))
			return false;

		drawInfo.mapCenterPos = tmpMapPoint;

		return SetMapPos(drawInfo.mapCenterPos);;
	}
	long MoveMap(Point point, Point centerPoint)
	{
		Point		tmpPoint;
		_dPoint		tmpMapPoint;
		Point		tmpCheckPoint;
		_dPoint		tmpCheckMapPoint;

		if (drawInfo.headingUpMode == GREEN_MAP_CONST::MAP_MODE_HEADING::MAP_MODE_HEADING_UP)
		{
			tmpPoint = Rotate(point, centerPoint, GetMapAngle());
			tmpCheckPoint = GetDeviceCenterPos();
			tmpCheckPoint.y = tmpCheckPoint.y + (centerPoint.y - GetDeviceCenterPos().y) - (centerPoint.y - tmpPoint.y);
			tmpCheckPoint.x = tmpCheckPoint.x - (centerPoint.x - tmpPoint.x);
		}
		else
		{
			tmpPoint = point;
			tmpCheckPoint = tmpPoint;
		}

		tmpMapPoint = DeviceToWorldMove(tmpPoint, centerPoint);
		tmpCheckMapPoint = DeviceToWorldMove(tmpCheckPoint, GetDeviceCenterPos());

		if ((tmpCheckMapPoint.x < 36) || (tmpCheckMapPoint.x > 54/*60*/) || (tmpCheckMapPoint.y < 8.8) || (tmpCheckMapPoint.y > 32))//30.2))
			return false;

		drawInfo.mapCenterPos = tmpMapPoint;

		return SetMapPos(drawInfo.mapCenterPos);;
	}

	long DrawMap();					// Shape Data Draw
	long DrawPolygon(_MapRecord* pData, double angle);						// Polygon Draw
	long DrawPolyline(_MapRecord* pData, double angle);					// Polyline Draw
	long DrawPOI(_MapRecord* pData, double angle);							// POI Data Draw
	long DrawBackground();																	// Background Draw
	bool IsDrawObject(Rect checkRect, Rect objRect, Rect drawRect);
	long DrawHSI();
	long DrawHomeGuide();
	long DrawCarImage();
	long DrawScaleBar();
	long DrawSymbol(_dPoint mapPoint, Image img, std::string text = "");
	long DrawSymbol(long staNum, long symbolType, _dPoint mapPoint, Color color, long lineSize, long angle = 0, bool isTooMsn = fasle);
	long DrawSymbol(long staNum, long symbolType, Point centerPoint, Color color, long lineSize, long angle = 0, bool isTooMsn = fasle);
	long DrawGuideLine(_dPoint basePoint, _dPoint targetPoint, long lineType, long lineSize, Color lineColor, Color BackColor);
	long DrawMission();
	long DrawUserLayer();
	long DrawListLine(_dPoint* inPointList, long pointCount, long lineType, long lineSize, long backLineSize, Color lineColor, Color BackColor, std::string text = "");
	long DrawRangeCircle(_dPoint inPoint, double distance, long lineType, long lineSize, long backLineSize, Color lineColor, Color BackColor, std::string text = "");
	long DrawOutLineText(Rect textRect, std::string textString, Color inColor, Color outColor);
	long DrawOutLineText(Rect textRect, std::string textString, Color inColor, Color outColor, unsigned int Position);

	Point Rotate(Point inPoint, Point centerPoint, long angle);
	_dPoint RotateDouble(_dPoint inPoint, _dPoint centerPoint, long angle);
	Rect GetBoundaryRect(Rect inRect, long angle);
	Point GetDevicePoint(Point inPoint, Point centerPoint, long anlge);

	Point WorldToDevice(const _dPoint _inPoint);
	Point WorldToDeviceUTM(const _dPoint _inPoint);
	_dPoint DeviceToWorld(const Point _inPoint);
	_dPoint DeviceToWorldMove(const Point _inPoint, Point centerPoint);

	long GetUTM(_dPoint inPoint, _dPoint& utmPoint, long param = 0);	// ��ǥ ��ȯ (WGS84 -> UTM)
	long GetUTM2KW(long izone, _dPoint utmPoint, _LatLonDMS& latlonDMS); // ��ǥ ��ȯ (UTM -> WGS84)

	std::string GetGP2MGRS(_dPoint inPoint);					// ��ǥ ��ȯ (WGS84 -> MGRS)
	std::string GetUTM2MGRS(int zone, _dPoint utmPoint);
	bool GetMGRS2KW(std::string mgrs, _LatLonDMS& kw);				// ��ǥ ��ȯ (MGRS -> WGS84)
	bool GetMGRS2UTM(std::string mgrs, _dPoint& utmPoint);

	Color colorConverter(int data);

public:

	MapDataManager			mapDataManager;
	_MapFactorInfo			_mapFactorInfo;
	_MapDrawInfo			drawInfo;					// Draw Window Information

	_dPoint					carPos;
	Brush					m_BACKBRUSH[2];
	Font					m_MapFont;
	Font					userLayerFont;
	Font					debugFont;

	Image					carImage;

	Image					imgHomeSymbol[2];

	Image					arrowHSI[2];

	Image					patternImage[2];

	long					m_CosValue[360];
	long					m_SinValue[360];
	int						m_BaseZone;

	Graphics* graphics;
};