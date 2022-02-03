#include "MapDrawEngine.h"
#include "AppLib.h"
#include "MyType.h"
#include "AppType.h"

#include <algorithm>
#include <vector>

#define MAX_DRAW_POINT_COUNT 8192
PointF GlDrawBuffer[MAX_DRAW_POINT_COUNT];

// CMapDrawEngine::CMapDrawEngine()
// {
// 	Color color = Color(0, 0, 0);
// 	Color color2 = Color(128, 255, 255);
// 	m_NULLPEN = Pen(color, 1.0);
// 	m_NULLBRUSH = Brush(color);
// 	m_BACKBRUSH = Brush(color2);

// 	graphics = new Graphics("/dev/fb0");

// 	Brush clear(Color(255, 255, 255));
// 	graphics->FillRectangle(&clear, RectF(0, 0, 800, 480));

// 	m_MapFont.SetFont("Sans-Regular");
// 	m_MapFont.SetSize(8);

// 	m_BaseZone = 52;

// 	double radius;

// 	for (long angleIdx = 0; angleIdx < 360; angleIdx++)
// 	{
// 		radius = (double)(angleIdx * 3.141592653589793238462643383279502884197169399375105820974944592308 / 180.);
// 		m_CosValue[angleIdx] = (long)(cos(radius) * 10000);
// 		m_SinValue[angleIdx] = (long)(sin(radius) * 10000);
// 	}

// 	debugIndex = 0;
// }

// CMapDrawEngine::~CMapDrawEngine()
// {
// }

// long CMapDrawEngine::Init()
// {
// 	long mapTypeIdx = 0;
// 	mapDataManager.Init();

// 	return true;
// }

// long CMapDrawEngine::DrawMap()
// {

// 	long nIdx = 0;

// 	Font oldFont = Font("Sans-Regular", 10);

// 	Color c = Color(0, 80, 255);
// 	Brush b = Brush(c);
// 	graphics->FillRectangle(&b, drawInfo.devRect.Rect2RectF());

// 	std::list<_MapRecord>::iterator pos = mapDataManager._drawData._drawDataList.begin();
// 	std::list<_MapRecord>::iterator eee = mapDataManager._drawData._drawDataList.end();
// 	_MapRecord pData;

// 	for (pos; pos != eee; pos++)
// 	{
// 		pData = *pos;
// 		switch (pData.header.objType)
// 		{
// 		case 1:
// 			DrawPOI(&pData, drawInfo.mapAngle, nIdx);
// 			break;
// 		case 3:
// 			DrawPolyline(&pData, drawInfo.mapAngle, nIdx);
// 			break;
// 		case 5:
// 			DrawPolygon(&pData, drawInfo.mapAngle, nIdx);
// 			std::cout << "poly poly\n";
// 			break;
// 		default:
// 			break;
// 		}
// 	}

// 	Color red = Color(255, 0, 0);
// 	Brush testBrush = Brush(red);
// 	Rect tmpRect;
// 	tmpRect.left = drawInfo.devCenterPos.x - 5;
// 	tmpRect.top = drawInfo.devCenterPos.y - 5;
// 	tmpRect.right = drawInfo.devCenterPos.x + 5;
// 	tmpRect.bottom = drawInfo.devCenterPos.y + 5;

// 	graphics->FillRectangle(&testBrush, tmpRect.Rect2RectF());

// 	return true;
// }

// Rect CMapDrawEngine::GetBoundaryRect(Rect inRect, long angle)
// {
// 	long minX = 999999;
// 	long minY = 999999;
// 	long maxX = 0;
// 	long maxY = 0;
// 	long index = 0;

// 	Rect retRect;
// 	Point inPoint[4];
// 	Point centerPoint = drawInfo.devCenterPos;

// 	inPoint[0] = Point(inRect.left, inRect.top);
// 	inPoint[1] = Point(inRect.right, inRect.top);
// 	inPoint[2] = Point(inRect.left, inRect.bottom);
// 	inPoint[3] = Point(inRect.right, inRect.bottom);

// 	for (index = 0; index < 4; index++)
// 	{
// 		inPoint[index] = Rotate(inPoint[index], centerPoint, angle);
// 		if (minX > inPoint[index].x)
// 			minX = inPoint[index].x;
// 		if (minY > inPoint[index].y)
// 			minY = inPoint[index].y;
// 		if (maxX < inPoint[index].x)
// 			maxX = inPoint[index].x;
// 		if (maxY < inPoint[index].y)
// 			maxY = inPoint[index].y;
// 	}

// 	retRect = Rect(minX, minY, maxX, maxY);

// 	return retRect;
// }

// bool CMapDrawEngine::IsDrawObject(Rect drawRect, Rect objRect)
// {
// 	Point checkPoint;
// 	Rect inRect = objRect;
// 	Rect cmpRect = drawRect;
// 	if ((drawRect.Width() < objRect.Width()) || (drawRect.Height() < objRect.Height()))
// 	{
// 		inRect = drawRect;
// 		cmpRect = objRect;
// 	}

// 	checkPoint = inRect.TopLeft();
// 	if (cmpRect.PtInRect(checkPoint) == true)
// 		return true;

// 	checkPoint = inRect.TopLeft();
// 	if (cmpRect.PtInRect(checkPoint) == true)
// 		return true;

// 	checkPoint.x = inRect.right;
// 	checkPoint.y = inRect.top;
// 	if (cmpRect.PtInRect(checkPoint) == true)
// 		return true;

// 	checkPoint.x = inRect.left;
// 	checkPoint.y = inRect.bottom;
// 	if (cmpRect.PtInRect(checkPoint) == true)
// 		return true;

// 	return false;
// }

// long CMapDrawEngine::DrawPolygon(_MapRecord *pData, double angle, long bufferIdx)
// {
// 	// for intersect calculation..
// 	Rect objRect(pData->header.boundaryRect);
// 	Rect drawRect;
// 	Rect checkRect;
// 	Rect rectBuffer;
// 	Point centerPoint;
// 	Point outPoint;
// 	Point inPoint;
// 	Point textPoint;
// 	Rect textRect;
// 	Point tmpCenterPoint(drawInfo.mapCenterPos4096);
// 	long nIdx = 0;
// 	Point textSize;
// 	std::string textData;

// 	Color color = Color(0, 0, 0);
// 	Brush oldBrush = Brush(color);
// 	Brush fillBrush = Brush(color);
// 	bool check = false;
// 	Pen drawPen = Pen(color, 1.0);
// 	Pen oldPen = Pen(color, 1.0);
// 	Font font("Sans-Regular", 10);

// 	_DesignRecord *designInfo = mapDataManager._designRecordMng.GetRecordData(pData->header.designCode);

// 	centerPoint = drawInfo.devCenterPos;

// 	tmpCenterPoint.x <<= drawInfo.logicalLevel;
// 	tmpCenterPoint.y <<= drawInfo.logicalLevel;

// 	objRect.left <<= drawInfo.logicalLevel;
// 	objRect.right <<= drawInfo.logicalLevel;
// 	objRect.top <<= drawInfo.logicalLevel;
// 	objRect.bottom <<= drawInfo.logicalLevel;

// 	drawRect.SetRect(tmpCenterPoint.x - drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y - drawInfo.drawRect.CenterPoint().y,
// 					tmpCenterPoint.x + drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y + drawInfo.drawRect.CenterPoint().y);

// 	textPoint = objRect.CenterPoint();
// 	checkRect = drawRect;
// 	long xGap = centerPoint.x - drawInfo.devRect.CenterPoint().x;
// 	long yGap = centerPoint.y - drawInfo.devRect.CenterPoint().y;

// 	if (xGap < 0)
// 		xGap = -xGap;
// 	if (yGap < 0)
// 		yGap = -yGap;

// 	xGap = (long)(4096. * xGap / 800.);
// 	yGap = (long)(4096. * yGap / 800.);
// 	checkRect.left -= xGap;
// 	checkRect.top -= yGap;
// 	checkRect.right += xGap;
// 	checkRect.bottom += yGap;

// 	if (drawInfo.headingUpMode == 1)
// 	{
// 		objRect = GetBoundaryRect(objRect, (long)angle);
// 		checkRect = GetBoundaryRect(checkRect, (long)angle);
// 	}

// 	// Text Point Calculate
// 	textData = pData->header.textData;
// 	if (!rectBuffer.IntersectRect(&checkRect, &objRect))
// 	{
// 		return false;
// 	}

// 	memset(&g_DrawBuffer, 0, sizeof(PointF) * MAX_DRAW_POINT_COUNT);
// 	for (nIdx = 0; nIdx < pData->header.pointCount; nIdx++)
// 	{
// 		inPoint = pData->pointList[nIdx];

// 		inPoint.x <<= drawInfo.logicalLevel;
// 		inPoint.y <<= drawInfo.logicalLevel;

// 		inPoint.x -= drawRect.left;
// 		inPoint.y -= drawRect.top;

// 		outPoint.x = (long)((800. / 4096.) * inPoint.x);
// 		outPoint.y = (long)((800. / 4096.) * inPoint.y);
// 		outPoint.y = drawInfo.devRect.bottom - outPoint.y;

// 		outPoint.x = outPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
// 		outPoint.y = outPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

// 		if (drawInfo.headingUpMode == 1)
// 		{
// 			g_DrawBuffer[nIdx] = Rotate(outPoint, centerPoint, (long)angle).Point2PointF();
// 		}
// 		else
// 		{
// 			g_DrawBuffer[nIdx] = outPoint.Point2PointF();
// 		}
// 	}

// 	if (designInfo != nullptr)
// 	{
// 		if (designInfo->objType == (unsigned char)2)
// 		{
// 			// fillBursh = CreateSolidBrush(designInfo->_brush[drawInfo.dayNightMode].fillValue.data);

// 			Color brushColor = colorConverter(designInfo->_brush[drawInfo.dayNightMode].fillValue.data);
// 			fillBrush.SetColor(brushColor);
// 			oldBrush = fillBrush;
// 			check = true;
// 		}
// 		if (designInfo->_line[drawInfo.dayNightMode].type == (unsigned char)5)
// 		{
// 			Color color = Color(255, 255, 255);
// 			drawPen = Pen(color, 0);
// 		}
// 		else
// 		{
// 			// drawPen = CreatePen(designInfo->_line[drawInfo.dayNightMode].type, designInfo->_line[drawInfo.dayNightMode].width, designInfo->_line[drawInfo.dayNightMode].color);
// 			Color color = colorConverter(designInfo->_line[drawInfo.dayNightMode].color);
// 			drawPen.SetColor(color);
// 		}
// 		oldPen = drawPen;
// 	}

// 	int cntPoint = pData->header.pointCount;
// 	if (cntPoint > 2 && check)
// 	{
// 		std::cout << std::endl << "-------------------------" << std::endl;
// 		std::cout << pData->header.objCode.codeValue[0] << " , " << pData->header.objCode.codeValue[1] << std::endl;
// 		graphics->FillPolygon(&(fillBrush), g_DrawBuffer, cntPoint);
// 		debugIndex++;
// 	}
// 	graphics->DrawPolygon(&(drawPen), g_DrawBuffer, cntPoint);

// 	// Text Output
// 	if ((textData.length() > 0) && (designInfo != nullptr))
// 	{
// 		textPoint.x -= drawRect.left;
// 		textPoint.y -= drawRect.top;

// 		textPoint.x = (long)((800. / 4096.) * textPoint.x);
// 		textPoint.y = (long)((800. / 4096.) * textPoint.y);
// 		textPoint.y = drawInfo.devRect.bottom - textPoint.y;

// 		textPoint.x = textPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
// 		textPoint.y = textPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

// 		if (drawInfo.headingUpMode == 1)
// 		{
// 			textPoint = Rotate(textPoint, centerPoint, (long)angle);
// 		}
// 		textSize.x += 4;
// 		textSize.y += 4;

// 		textRect.left = textPoint.x - (int)(textSize.x / 2) - 1;
// 		textRect.right = textPoint.x + (int)(textSize.x / 2) + 1;
// 		textRect.top = textPoint.y - (int)(textSize.y / 2) - 1;
// 		textRect.bottom = textPoint.y + (int)(textSize.y / 2) + 1;

// 		// SetTextColor(hDC, designInfo->_fontStyle[drawInfo.dayNightMode].color);
// 		font.SetFont("Sans-Regular");
// 		font.SetSize(20);

// 		Color ccc(0, 0, 0);
// 		Brush bbb(ccc);
// 		Font fff("Sans-Regular", 10);
// 		graphics->DrawString(pData->header.textData, -1, &fff, textRect.TopLeft().Point2PointF(), &bbb);
// 	}

// 	return true;
// }

// long CMapDrawEngine::DrawPolyline(_MapRecord *pData, double angle, long bufferIdx)
// {
// 	Rect objRect = pData->header.boundaryRect;
// 	Rect drawRect;
// 	Rect checkRect;
// 	Rect rectBuffer;
// 	Point centerPoint;
// 	Point outPoint;
// 	Point inPoint;
// 	Point tmpCenterPoint = drawInfo.mapCenterPos4096;
// 	long nIdx = 0;

// 	Color color = Color(0, 255, 0);
// 	Pen drawPen = Pen(color, 1.0);
// 	Pen oldPen = Pen(color, 1.0);

// 	_DesignRecord *designInfo = mapDataManager._designRecordMng.GetRecordData(pData->header.designCode);

// 	centerPoint = drawInfo.devCenterPos;

// 	tmpCenterPoint.x <<= drawInfo.logicalLevel;
// 	tmpCenterPoint.y <<= drawInfo.logicalLevel;

// 	objRect.left <<= drawInfo.logicalLevel;
// 	objRect.right <<= drawInfo.logicalLevel;
// 	objRect.top <<= drawInfo.logicalLevel;
// 	objRect.bottom <<= drawInfo.logicalLevel;

// 	drawRect.SetRect(tmpCenterPoint.x - drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y - drawInfo.drawRect.CenterPoint().y,
// 					tmpCenterPoint.x + drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y + drawInfo.drawRect.CenterPoint().y);

// 	checkRect = drawRect;
// 	long xGap = centerPoint.x - drawInfo.devRect.CenterPoint().x;
// 	long yGap = centerPoint.y - drawInfo.devRect.CenterPoint().y;

// 	if (xGap < 0)
// 		xGap = -xGap;
// 	if (yGap < 0)
// 		yGap = -yGap;

// 	xGap = (long)(4096. * xGap / 800.);
// 	yGap = (long)(4096. * yGap / 800.);
// 	checkRect.left -= xGap;
// 	checkRect.top -= yGap;
// 	checkRect.right += xGap;
// 	checkRect.bottom += yGap;

// 	if (drawInfo.headingUpMode == 1)
// 	{
// 		objRect = GetBoundaryRect(objRect, (long)angle);
// 		checkRect = GetBoundaryRect(checkRect, (long)angle);
// 	}

// 	if (!rectBuffer.IntersectRect(&checkRect, &objRect))
// 	{
// 		return false;
// 	}

// 	memset(&g_DrawBuffer, 0, sizeof(Point) * MAX_DRAW_POINT_COUNT);
// 	for (nIdx = 0; nIdx < pData->header.pointCount; nIdx++)
// 	{
// 		inPoint = pData->pointList[nIdx];

// 		inPoint.x <<= drawInfo.logicalLevel;
// 		inPoint.y <<= drawInfo.logicalLevel;

// 		inPoint.x -= drawRect.left;
// 		inPoint.y -= drawRect.top;

// 		outPoint.x = (long)((800. / 4096.) * inPoint.x);
// 		outPoint.y = (long)((800. / 4096.) * inPoint.y);
// 		outPoint.y = drawInfo.devRect.bottom - outPoint.y;

// 		outPoint.x = outPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
// 		outPoint.y = outPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

// 		if (drawInfo.headingUpMode == 1)
// 		{
// 			g_DrawBuffer[nIdx] = Rotate(outPoint, centerPoint, (long)angle).Point2PointF();
// 		}
// 		else
// 		{
// 			g_DrawBuffer[nIdx] = outPoint.Point2PointF();
// 		}
// 	}

// 	if (designInfo != nullptr)
// 	{
// 		if (designInfo->_line[drawInfo.dayNightMode].type == (unsigned char)5)
// 		{
// 			return true;
// 		}
// 		else
// 		{
// 			Color color = colorConverter(designInfo->_line[drawInfo.dayNightMode].color);
// 			drawPen.SetColor(color);
// 			graphics->DrawLines(&drawPen, g_DrawBuffer, nIdx);
// 		}
// 	}
// 	return true;
// }

// long CMapDrawEngine::DrawPOI(_MapRecord *pData, double angle, long bufferIdx)
// {
// 	Rect drawRect;
// 	Rect checkRect;
// 	Rect objRect;
// 	Rect rectBuffer;
// 	Point centerPoint;
// 	Point outPoint;
// 	Point inPoint;
// 	Point tmpCenterPoint = drawInfo.mapCenterPos4096;
// 	Point textSize;
// 	Rect textRect;
// 	std::string FieldValue;

// 	Font font("Sans-Regular", 10);
// 	Color color = Color(255, 255, 255);
// 	Brush fillBrush = Brush(color);

// 	FieldValue = pData->header.textData;
// 	centerPoint = drawInfo.devCenterPos;
// 	inPoint = pData->pointList[0];

// 	tmpCenterPoint.x <<= drawInfo.logicalLevel;
// 	tmpCenterPoint.y <<= drawInfo.logicalLevel;

// 	inPoint.x <<= drawInfo.logicalLevel;
// 	inPoint.y <<= drawInfo.logicalLevel;

// 	objRect.SetRect(inPoint.x - 1, inPoint.y - 1, inPoint.x + 1, inPoint.y + 1);
// 	drawRect.SetRect(tmpCenterPoint.x - drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y - drawInfo.drawRect.CenterPoint().y,
// 					tmpCenterPoint.x + drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y + drawInfo.drawRect.CenterPoint().y);

// 	checkRect = drawRect;
// 	if (drawInfo.headingUpMode == 1)
// 	{
// 		checkRect = GetBoundaryRect(drawRect, (long)angle);
// 		objRect = GetBoundaryRect(objRect, (long)angle);
// 	}
// 	if (!rectBuffer.IntersectRect(&checkRect, &objRect))
// 	{
// 		return false;
// 	}
// 	inPoint.x -= drawRect.left;
// 	inPoint.y -= drawRect.top;

// 	outPoint.x = (long)((800. / 4096.) * inPoint.x);
// 	outPoint.y = (long)((800. / 4096.) * inPoint.y);
// 	outPoint.y = drawInfo.devRect.bottom - outPoint.y;

// 	outPoint.x = outPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
// 	outPoint.y = outPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

// 	if (drawInfo.headingUpMode == 1)
// 	{
// 		g_DrawBuffer[0] = Rotate(outPoint, centerPoint, (long)angle).Point2PointF();
// 	}
// 	else
// 	{
// 		g_DrawBuffer[0] = outPoint.Point2PointF();
// 	}
// 	textSize.x += 4;
// 	textSize.y += 4;

// 	textRect.left = g_DrawBuffer[0].X - (int)(textSize.x / 2) - 1;
// 	textRect.right = g_DrawBuffer[0].X + (int)(textSize.x / 2) + 1;
// 	textRect.top = g_DrawBuffer[0].Y - (int)(textSize.y / 2) - 1;
// 	textRect.bottom = g_DrawBuffer[0].Y + (int)(textSize.y / 2) + 1;

// 	if (drawInfo.dayNightMode == 0)
// 		fillBrush.SetColor(Color(0, 0, 0));
// 	else
// 		fillBrush.SetColor(Color(255, 255, 255));

// 	RectF tmpRectF = textRect.Rect2RectF();
// 	font.SetFont("Sans-Regular");
// 	font.SetSize(10);
// 	graphics->DrawString(FieldValue.c_str(), -1, &font, textRect.TopLeft().Point2PointF(), &fillBrush);

// 	return true;
// }

// Point CMapDrawEngine::Rotate(Point inPoint, Point centerPoint, long angle)
// {
// 	Point outPoint;

// 	angle %= 360;

// 	long cosValue = m_CosValue[angle];
// 	long sinValue = m_SinValue[angle];

// 	inPoint.x -= centerPoint.x;
// 	inPoint.y -= centerPoint.y;

// 	outPoint.x = (inPoint.x * cosValue - inPoint.y * sinValue) / 10000;
// 	outPoint.y = (inPoint.y * cosValue + inPoint.x * sinValue) / 10000;

// 	outPoint.x += centerPoint.x;
// 	outPoint.y += centerPoint.y;

// 	return outPoint;
// }

// Point CMapDrawEngine::WorldToDevice(const _dPoint _inPoint)
// {
// 	Point retPoint;

// 	double xPos = (long)((_inPoint.x * 28800.) - drawInfo.mapCenterPos.x);
// 	double yPos = (long)((_inPoint.y * 28800.) - drawInfo.mapCenterPos.y);

// 	long level = _mapFactorInfo.GetTableLevel(0);
// 	long xGap = _mapFactorInfo._levelGapTable[1][level];
// 	long yGap = _mapFactorInfo._levelGapTable[0][level];

// 	retPoint.x = (drawInfo.devCenterPos.x + ((long)(xPos * 800. / xGap) << drawInfo.logicalLevel));
// 	retPoint.y = (drawInfo.devCenterPos.y - ((long)(yPos * 800. / yGap) << drawInfo.logicalLevel));

// 	return retPoint;
// }
// _dPoint CMapDrawEngine::DeviceToWorld(const Point _inPoint)
// {
// 	return DeviceToWorldMove(_inPoint, drawInfo.devCenterPos);
// }
// _dPoint CMapDrawEngine::DeviceToWorldMove(const Point _inPoint, Point centerPoint)
// {
// 	_dPoint retPoint;
// 	Point deltaPoint;
// 	_dPoint deltaMapPoint;
// 	Point mapCenterPoint = drawInfo.mapCenterPos4096;

// 	deltaPoint.x = centerPoint.x - _inPoint.x;
// 	deltaPoint.y = _inPoint.y - centerPoint.y;

// 	deltaPoint.x >>= drawInfo.logicalLevel;
// 	deltaPoint.y >>= drawInfo.logicalLevel;

// 	deltaMapPoint.x = 4096.;
// 	deltaMapPoint.y = 4096.;

// 	deltaMapPoint.x = deltaPoint.x * deltaMapPoint.x / 800.;
// 	deltaMapPoint.y = deltaPoint.y * deltaMapPoint.y / 800.;

// 	mapCenterPoint.x -= (long)deltaMapPoint.x;
// 	mapCenterPoint.y -= (long)deltaMapPoint.y;

// 	retPoint.x = _mapFactorInfo._basePoint.x + (long)((double)mapCenterPoint.x / _mapFactorInfo._levelFactorTable[1][_mapFactorInfo.GetTableLevel(0)]);
// 	retPoint.y = _mapFactorInfo._basePoint.y + (long)((double)mapCenterPoint.y / _mapFactorInfo._levelFactorTable[0][_mapFactorInfo.GetTableLevel(0)]);

// 	retPoint.x = retPoint.x / 28800.;
// 	retPoint.y = retPoint.y / 28800.;

// 	return retPoint;
// }

// long CMapDrawEngine::GetUTM(_dPoint inPoint, _dPoint &utmPoint, long param)
// {
// 	KW kw;
// 	double tutmx = 0.;
// 	double tutmy = 0.;
// 	double slam = 0.;
// 	double sphi = 0.;
// 	int tmp_zone = 0;

// 	double tutmxt = 0.;
// 	double tutmyt = 0.;

// 	m_Coordinate._dCentralKd = 127;
// 	m_Coordinate.GetKwbyXY(inPoint.y, inPoint.x, &kw);
// 	slam = m_Coordinate.GetRadian(kw.kd, kw.kb, kw.kc);
// 	sphi = m_Coordinate.GetRadian(kw.wd, kw.wb, kw.wc);

// 	m_Coordinate.GetTawon2utm(0, sphi, slam, &m_BaseZone, &tutmy, &tutmx, 0);

// 	utmPoint.x = tutmx;
// 	utmPoint.y = tutmy;

// 	if (param == 0)
// 	{
// 		if (m_BaseZone == 52)
// 		{
// 			utmPoint.x = tutmx;
// 			utmPoint.y = tutmy;
// 		}
// 		else
// 		{
// 			tmp_zone = 52;
// 			m_Coordinate.GetTawon2utm(0, sphi, slam, &tmp_zone, &tutmy, &tutmx, 1);
// 			utmPoint.x = tutmx;
// 			utmPoint.y = tutmy;
// 		}
// 	}
// 	else
// 	{
// 		utmPoint.x = tutmx;
// 		utmPoint.y = tutmy;
// 	}
// 	return m_BaseZone;
// }

// long CMapDrawEngine::GetUTM2KW(long izone, _dPoint utmPoint, KW &kw)
// {
// 	double sphi = 0.;
// 	double slam = 0.;

// 	m_Coordinate.GetUtm2Tawon(0, &sphi, &slam, izone, utmPoint.y, utmPoint.x);
// 	m_Coordinate.GetUtm2Tawon(BESSEL, &sphi, &slam, izone, utmPoint.y, utmPoint.x);
// 	m_Coordinate.GetDMS(sphi, &kw.wd, &kw.wb, &kw.wc);
// 	m_Coordinate.GetDMS(slam, &kw.kd, &kw.kb, &kw.kc);

// 	return true;
// }

// std::string CMapDrawEngine::GetGP2MGRS(_dPoint inPoint)
// {
// 	return m_Coordinate.gp2mgrs(0, inPoint.y, inPoint.x);
// }

// bool CMapDrawEngine::GetMGRS2KW(std::string mgrs, KW &kw)
// {
// 	return m_Coordinate.mgrs2gp(0, mgrs, kw);
// }

// std::string CMapDrawEngine::GetUTM2MGRS(int zone, _dPoint utmPoint)
// {
// 	return m_Coordinate.utm2mgrs(0, zone, utmPoint.x, utmPoint.y);
// }

// bool CMapDrawEngine::GetMGRS2UTM(std::string mgrs, _dPoint &utmPoint)
// {
// 	return m_Coordinate.mgrs2utm(0, mgrs, utmPoint.x, utmPoint.y);
// }

Color CMapDrawEngine::colorConverter(int data)
{
	int hexa[8];
	int decimal = data;
	for (int i = 7; i >= 0; i--)
	{
		hexa[i] = decimal % 16;
		decimal /= 16;
	}
	int r = hexa[6] * 16 + hexa[7];
	int g = hexa[4] * 16 + hexa[5];
	int b = hexa[2] * 16 + hexa[3];
	int a = hexa[0] * 16 + hexa[1];

	return Color(a, r, g, b);
}

CMapDrawEngine::CMapDrawEngine()
{
	graphics = new Graphics("/dev/fb0");

	m_BACKBRUSH[0] = Color(255, 80, 131, 183);
	m_BACKBRUSH[1] = Color(255, 0, 0, 0);

	m_MapFont.SetFont("Sans-Regular");
	m_MapFont.SetSize(8);

	// carImage = CAppLib::LoadResourceImage(ImgFileName);
	// arrowHSI[0] = CAppLib::LoadResourceImage(ImgFileName);
	// arrowHSI[1] = CAppLib::LoadResourceImage(ImgFileName);
	// imgHomeSymbol[0] = CAppLib::LoadResourceImage(ImgFileName);
	// imgHomeSymbol[1] = CAppLib::LoadResourceImage(ImgFileName);
	// patternImage[0] = CAppLib::LoadResourceImage(ImgFileName);
	// patternImage[1] = CAppLib::LoadResourceImage(ImgFileName);

	m_BaseZone = 40;

	double radius;
	long factor = 1;
	factor <<= 14;

	for (long angleIdx = 0; angleIdx < 360; angleIdx++)
	{
		radius = (double)(angleIdx * GREEN_MAP_CONST::PI_VALUE / 180.);
		m_CosValue[angleIdx] = (long)(cos(radius) * factor);
		m_SinValue[angleIdx] = (long)(sin(radius) * factor);
	}
}

CMapDrawEngine::~CMapDrawEngine()
{
	// Init();
}

long CMapDrawEngine::Init()
{
	mapDataManager.Init();

	return true;
}

long		g_tmpPointCount = 0;
long		g_TotalPointCount = 0;

long CMapDrawEngine::DrawMap()
{
	g_TotalPointCount = 0;

	//SetBkMode(hDC, TRANSPARENT);
	graphics->FillRectangle(&m_BACKBRUSH[drawInfo.dayNightMode], drawInfo.devRect.Rect2RectF());
	_MapRecord pData;

	std::list<_MapRecord>::iterator pos = mapDataManager._drawData._drawDataList.begin();
	std::list<_MapRecord>::iterator eee = mapDataManager._drawData._drawDataList.end();

	for (pos; pos != eee; pos++) {
		pData = *pos;
		if (drawInfo.logicalLevel < 5)
		{
			if ((strcmp(pData.header.textLayerDes, "��") == 0) ||
				(strcmp(pData.header.textLayerDes, "ö��") == 0) ||
				(strcmp(pData.header.textLayerDes, "Ȱ�ַ�") == 0) ||
				(strcmp(pData.header.textLayerDes, "����") == 0))
			{
				continue;
			}
		}

		if ((strcmp(pData.header.textLayerDes, "����") == 0) && (pData.header.isVisible == false))
		{
			continue;
		}

		switch (pData.header.objType)
		{
		case 1:
			DrawPOI(&pData, drawInfo.mapAngle);
			break;
		case 3:
			DrawPolyline(&pData, drawInfo.mapAngle);
			break;
		case 5:
			DrawPolygon(&pData, drawInfo.mapAngle);
			break;
		default:
			break;
		}
	}

	DrawUserLayer();

	DrawMission();

	// HSI Draw
	if (drawInfo.headingUpMode == (long)1)
		DrawHSI();

	// Car Image Draw
	DrawCarImage();
	DrawScaleBar();

#if 0 //IS_DYNAMIC_LOG > 0

	if (GlAppState.isDisplayDynamicDebugMsg != false)
	{
		SelectObject(hDC, debugFont);
		long drawIndex = 0;
		long baseX = 80;
		long baseY = 280;
		long gapValue = 18;
		Rect drawTextRectL = Rect(baseX, baseY, baseX + 200, baseY + gapValue);
		Rect drawTextRectR = Rect(baseX + 200, baseY, baseX + 400, baseY + gapValue);
		Rect drawTextRectC = Rect(baseX, baseY, baseX + 400, baseY + gapValue);

		DrawOutLineText(hDC, drawTextRectL, inWindSpeedMsg, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
		DrawOutLineText(hDC, drawTextRectR, inWindHead, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
		drawTextRectL.top += gapValue;
		drawTextRectL.bottom += gapValue;
		drawTextRectR.top += gapValue;
		drawTextRectR.bottom += gapValue;
		drawTextRectC.top += gapValue;
		drawTextRectC.bottom += gapValue;
		DrawOutLineText(hDC, drawTextRectL, inTemperature, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
		DrawOutLineText(hDC, drawTextRectR, inAlt, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
		drawTextRectL.top += gapValue;
		drawTextRectL.bottom += gapValue;
		drawTextRectR.top += gapValue;
		drawTextRectR.bottom += gapValue;
		drawTextRectC.top += gapValue;
		drawTextRectC.bottom += gapValue;
		DrawOutLineText(hDC, drawTextRectL, innV, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
		DrawOutLineText(hDC, drawTextRectR, indV, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
		drawTextRectL.top += gapValue;
		drawTextRectL.bottom += gapValue;
		drawTextRectR.top += gapValue;
		drawTextRectR.bottom += gapValue;
		drawTextRectC.top += gapValue;
		drawTextRectC.bottom += gapValue;
		DrawOutLineText(hDC, drawTextRectL, ineV, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
		drawTextRectL.top += gapValue;
		drawTextRectL.bottom += gapValue;
		drawTextRectR.top += gapValue;
		drawTextRectR.bottom += gapValue;
		drawTextRectC.top += gapValue;
		drawTextRectC.bottom += gapValue;
		DrawOutLineText(hDC, drawTextRectC, inTargetPoint, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
		drawTextRectL.top += gapValue;
		drawTextRectL.bottom += gapValue;
		drawTextRectR.top += gapValue;
		drawTextRectR.bottom += gapValue;
		drawTextRectC.top += gapValue;
		drawTextRectC.bottom += gapValue;

		for (drawIndex = 0; drawIndex < 8; drawIndex++)
		{
			if (inWayListPoint[drawIndex].Find(L"None") >= 0)
				continue;

			DrawOutLineText(hDC, drawTextRectC, inWayListPoint[drawIndex], GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
			drawTextRectL.top += gapValue;
			drawTextRectL.bottom += gapValue;
			drawTextRectR.top += gapValue;
			drawTextRectR.bottom += gapValue;
			drawTextRectC.top += gapValue;
			drawTextRectC.bottom += gapValue;
		}

		for (drawIndex = 0; drawIndex < 10; drawIndex++)
		{
			if (inInZoneListPoint[drawIndex].Find(L"None") >= 0)
				continue;
			DrawOutLineText(hDC, drawTextRectC, inInZoneListPoint[drawIndex], GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
			drawTextRectL.top += gapValue;
			drawTextRectL.bottom += gapValue;
			drawTextRectR.top += gapValue;
			drawTextRectR.bottom += gapValue;
			drawTextRectC.top += gapValue;
			drawTextRectC.bottom += gapValue;
		}

		DrawOutLineText(hDC, drawTextRectL, outWindHead, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
		DrawOutLineText(hDC, drawTextRectR, outWindSpeed, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
		drawTextRectL.top += gapValue;
		drawTextRectL.bottom += gapValue;
		drawTextRectR.top += gapValue;
		drawTextRectR.bottom += gapValue;
		drawTextRectC.top += gapValue;
		drawTextRectC.bottom += gapValue;

		for (drawIndex = 0; drawIndex < 4; drawIndex++)
		{
			DrawOutLineText(hDC, drawTextRectC, outInZoneListPoint[drawIndex], GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
			drawTextRectL.top += gapValue;
			drawTextRectL.bottom += gapValue;
			drawTextRectR.top += gapValue;
			drawTextRectR.bottom += gapValue;
			drawTextRectC.top += gapValue;
			drawTextRectC.bottom += gapValue;
		}

		DrawOutLineText(hDC, drawTextRectL, outTooPoint, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
		DrawOutLineText(hDC, drawTextRectR, outTooMinMaxRange, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
		drawTextRectL.top += gapValue;
		drawTextRectL.bottom += gapValue;
		drawTextRectR.top += gapValue;
		drawTextRectR.bottom += gapValue;
		drawTextRectC.top += gapValue;
		drawTextRectC.bottom += gapValue;

		DrawOutLineText(hDC, drawTextRectC, timeValue, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR, DT_LEFT);
	}
#endif

	return true;
}

Point CMapDrawEngine::GetDevicePoint(Point inPoint, Point centerPoint, long anlge)
{
	Point retPoint;
	Point outPoint;

	inPoint.x -= centerPoint.x;
	inPoint.y -= centerPoint.y;

	outPoint.x = (long)((800. / 4096.) * inPoint.x);
	outPoint.y = (long)((600. / 4096.) * inPoint.y);
	outPoint.y = drawInfo.devRect.bottom - outPoint.y;

	outPoint.x = outPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
	outPoint.y = outPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

	if (drawInfo.headingUpMode == (long)1)
	{
		retPoint = Rotate(outPoint, drawInfo.devCenterPos, anlge);
	}
	else
	{
		retPoint = outPoint;
	}

	return retPoint;
}

Rect CMapDrawEngine::GetBoundaryRect(Rect inRect, long angle)
{
	long minX = 999999;
	long minY = 999999;
	long maxX = 0;
	long maxY = 0;
	long index = 0;

	Rect retRect;
	Point inPoint[4];
	Point centerPoint = drawInfo.mapCenterPos4096;

	inPoint[0] = Point(inRect.left, inRect.top);
	inPoint[1] = Point(inRect.right, inRect.top);
	inPoint[2] = Point(inRect.left, inRect.bottom);
	inPoint[3] = Point(inRect.right, inRect.bottom);

	for (index = 0; index < 4; index++)
	{
		inPoint[index] = Rotate(inPoint[index], centerPoint, angle);
		if (minX > inPoint[index].x)
			minX = inPoint[index].x;
		if (minY > inPoint[index].y)
			minY = inPoint[index].y;
		if (maxX < inPoint[index].x)
			maxX = inPoint[index].x;
		if (maxY < inPoint[index].y)
			maxY = inPoint[index].y;
	}

	retRect = Rect(minX, minY, maxX, maxY);

	return retRect;
}

bool CMapDrawEngine::IsDrawObject(Rect checkRect, Rect objRect, Rect drawRect)
{
	Rect		rectBuffer;

	if (drawInfo.headingUpMode == (long)1)
	{
		long minX = 999999;
		long minY = 999999;
		long maxX = 0;
		long maxY = 0;
		long index = 0;
		Point tmpPoint[4];

		tmpPoint[0] = Point(objRect.left, objRect.top);
		tmpPoint[1] = Point(objRect.right, objRect.top);
		tmpPoint[2] = Point(objRect.left, objRect.bottom);
		tmpPoint[3] = Point(objRect.right, objRect.bottom);

		for (index = 0; index < 4; index++)
			tmpPoint[index] = GetDevicePoint(tmpPoint[index], drawRect.TopLeft(), (long)drawInfo.mapAngle);

		for (index = 0; index < 4; index++)
		{
			if (minX > tmpPoint[index].x)
				minX = tmpPoint[index].x;
			if (minY > tmpPoint[index].y)
				minY = tmpPoint[index].y;
			if (maxX < tmpPoint[index].x)
				maxX = tmpPoint[index].x;
			if (maxY < tmpPoint[index].y)
				maxY = tmpPoint[index].y;
		}
		objRect.left = minX;
		objRect.top = minY;
		objRect.right = maxX;
		objRect.bottom = maxY;

		checkRect = drawInfo.devRect;
	}

	if (!rectBuffer.IntersectRect(&checkRect, &objRect))
	{
		return false;
	}

	return true;
}

long CMapDrawEngine::DrawPolygon(_MapRecord* pData, double angle)
{
	// for intersect calculation..
	Rect		objRect = pData->header.boundaryRect;
	Rect		drawRect;
	Rect		checkRect;

	Point		centerPoint;
	Point		outPoint;
	Point		inPoint;
	Point		textPoint;
	Rect		textRect;
	Point		tmpCenterPoint = drawInfo.mapCenterPos4096;
	long		nIdx = 0;

	long		oldTextColor;

	std::string		textData;

	Brush		fillBrush(Color(0, 0, 0, 0));
	Pen			drawPen(Color(0, 0, 0, 0));
	bool		isNullBrush = false;
	bool		isNullPen = false;

	_DesignRecord* designInfo = mapDataManager._designRecordMng.GetRecordData(pData->header.designCode);

	if (designInfo == nullptr) return false;

	centerPoint = drawInfo.devCenterPos;

	if (drawInfo.logicalLevel < 4)
	{
		tmpCenterPoint.x <<= drawInfo.logicalLevel;
		tmpCenterPoint.y <<= drawInfo.logicalLevel;

		objRect.left <<= drawInfo.logicalLevel;
		objRect.right <<= drawInfo.logicalLevel;
		objRect.top <<= drawInfo.logicalLevel;
		objRect.bottom <<= drawInfo.logicalLevel;
	}
	else
	{
		tmpCenterPoint.x <<= (drawInfo.logicalLevel - 1);
		tmpCenterPoint.y <<= (drawInfo.logicalLevel - 1);

		objRect.left <<= (drawInfo.logicalLevel - 1);
		objRect.right <<= (drawInfo.logicalLevel - 1);
		objRect.top <<= (drawInfo.logicalLevel - 1);
		objRect.bottom <<= (drawInfo.logicalLevel - 1);

		if (drawInfo.logicalLevel == 4)
		{
			tmpCenterPoint.x = LongMultiDouble(tmpCenterPoint.x, 1.4);
			tmpCenterPoint.y = LongMultiDouble(tmpCenterPoint.y, 1.4);

			objRect.left = LongMultiDouble(objRect.left, 1.4);
			objRect.right = LongMultiDouble(objRect.right, 1.4);
			objRect.top = LongMultiDouble(objRect.top, 1.4);
			objRect.bottom = LongMultiDouble(objRect.bottom, 1.4);
		}
	}


	drawRect.SetRect(tmpCenterPoint.x - drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y - drawInfo.drawRect.CenterPoint().y,
		tmpCenterPoint.x + drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y + drawInfo.drawRect.CenterPoint().y);

	textPoint = objRect.CenterPoint();
	checkRect = drawRect;
	long xGap = centerPoint.x - drawInfo.devRect.CenterPoint().x;
	long yGap = centerPoint.y - drawInfo.devRect.CenterPoint().y;

	if (xGap < 0)
		xGap = -xGap;
	if (yGap < 0)
		yGap = -yGap;

	xGap = (long)(4096. * xGap / 800.);
	yGap = (long)(4096. * yGap / 600.);

	checkRect.left -= xGap;
	checkRect.top -= yGap;
	checkRect.right += xGap;
	checkRect.bottom += yGap;

	if (!IsDrawObject(checkRect, objRect, drawRect))
		return false;

	// Text Point Calculate
	if ((strlen(pData->header.textData) > 0) && (strlen(pData->header.textData) < 32))
	{
		textData = pData->header.textData;
	}

	if (g_tmpPointCount < pData->header.pointCount)
		g_tmpPointCount = pData->header.pointCount;

	memset(GlDrawBuffer, 0, sizeof(PointF) * MAX_DRAW_POINT_COUNT);
	for (nIdx = 0; nIdx < pData->header.pointCount; nIdx++)
	{
		inPoint = pData->pointList[nIdx];

		if (drawInfo.logicalLevel < 4)
		{
			inPoint.x <<= drawInfo.logicalLevel;
			inPoint.y <<= drawInfo.logicalLevel;
		}
		else
		{
			inPoint.x <<= (drawInfo.logicalLevel - 1);
			inPoint.y <<= (drawInfo.logicalLevel - 1);
			if (drawInfo.logicalLevel == 4)
			{
				inPoint.x = LongMultiDouble(inPoint.x, 1.4);
				inPoint.y = LongMultiDouble(inPoint.y, 1.4);
			}
		}


		inPoint.x -= drawRect.left;
		inPoint.y -= drawRect.top;

		outPoint.x = (long)((800. / 4096.) * inPoint.x);
		outPoint.y = (long)((600. / 4096.) * inPoint.y);
		outPoint.y = drawInfo.devRect.bottom - outPoint.y;

		outPoint.x = outPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
		outPoint.y = outPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

		if (drawInfo.headingUpMode == (long)1)
		{
			GlDrawBuffer[nIdx] = Rotate(outPoint, centerPoint, (long)angle).Point2PointF();
		}
		else
		{
			GlDrawBuffer[nIdx] = outPoint.Point2PointF();
		}
		g_TotalPointCount++;
	}

	if (designInfo->_brush[drawInfo.dayNightMode].type == DESIGN_CONST::DRAW_TYPE::BRUSH_TYPE::SOLID)//Null Pointer Dereference
		fillBrush.SetColor(colorConverter(designInfo->_brush[drawInfo.dayNightMode].fillValue.data));
	else
		// fillBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		isNullBrush = true;
	if (designInfo->_line[drawInfo.dayNightMode].type == DESIGN_CONST::DRAW_TYPE::LINE_TYPE::NULLPEN)
		// drawPen = (Pen)GetStockObject(NULL_PEN);
		isNullPen = true;
	else {
		// pen ��¦ �̻��ϴϱ� ���߿� �ٽ� ����
		drawPen.SetColor(colorConverter(designInfo->_line[drawInfo.dayNightMode].color));
		drawPen.SetWidth(designInfo->_line[drawInfo.dayNightMode].width);
		drawPen.SetDashStyle(designInfo->_line[drawInfo.dayNightMode].type);
	}

	int cntPoint = pData->header.pointCount;
	if (cntPoint > 2 && !isNullBrush)
		graphics->FillPolygon(&fillBrush, GlDrawBuffer, cntPoint);
	if (!isNullPen)
		graphics->DrawPolygon(&drawPen, GlDrawBuffer, cntPoint);

	// Text Output
	if (textData.length() > 0)
	{
		textPoint.x -= drawRect.left;
		textPoint.y -= drawRect.top;

		textPoint.x = (long)((800. / 4096.) * textPoint.x);
		textPoint.y = (long)((600. / 4096.) * textPoint.y);
		textPoint.y = drawInfo.devRect.bottom - textPoint.y;

		textPoint.x = textPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
		textPoint.y = textPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

		if (drawInfo.headingUpMode == (long)1)
		{
			textPoint = Rotate(textPoint, centerPoint, (long)angle);
		}


		textRect.left = textPoint.x - 1;
		textRect.right = textPoint.x + 1;
		textRect.top = textPoint.y - 1;
		textRect.bottom = textPoint.y + 1;

		Brush textBrush(colorConverter(designInfo->_fontStyle[drawInfo.dayNightMode].color));
		graphics->DrawString(textData.c_str(), -1, &m_MapFont, textRect.TopLeft().Point2PointF(), &textBrush);
		g_TotalPointCount++;
	}

	return true;
}

long CMapDrawEngine::DrawPolyline(_MapRecord* pData, double angle)
{
	Rect		objRect = pData->header.boundaryRect;
	Rect		drawRect;
	Rect		checkRect;
	Point		centerPoint;
	Point		outPoint;
	Point		inPoint;
	Point		tmpCenterPoint = drawInfo.mapCenterPos4096;
	long		nIdx = 0;
	Pen			drawPen(Color(0, 0, 0, 0));
	bool 		isNullPen = false;

	_DesignRecord* designInfo = mapDataManager._designRecordMng.GetRecordData(pData->header.designCode);

	if (designInfo == nullptr) return false;//110702

	centerPoint = drawInfo.devCenterPos;

	if (drawInfo.logicalLevel < 4)
	{
		tmpCenterPoint.x <<= drawInfo.logicalLevel;
		tmpCenterPoint.y <<= drawInfo.logicalLevel;

		objRect.left <<= drawInfo.logicalLevel;
		objRect.right <<= drawInfo.logicalLevel;
		objRect.top <<= drawInfo.logicalLevel;
		objRect.bottom <<= drawInfo.logicalLevel;
	}
	else
	{
		tmpCenterPoint.x <<= (drawInfo.logicalLevel - 1);
		tmpCenterPoint.y <<= (drawInfo.logicalLevel - 1);

		objRect.left <<= (drawInfo.logicalLevel - 1);
		objRect.right <<= (drawInfo.logicalLevel - 1);
		objRect.top <<= (drawInfo.logicalLevel - 1);
		objRect.bottom <<= (drawInfo.logicalLevel - 1);

		if (drawInfo.logicalLevel == 4)
		{
			tmpCenterPoint.x = LongMultiDouble(tmpCenterPoint.x, 1.4);
			tmpCenterPoint.y = LongMultiDouble(tmpCenterPoint.y, 1.4);

			objRect.left = LongMultiDouble(objRect.left, 1.4);
			objRect.right = LongMultiDouble(objRect.right, 1.4);
			objRect.top = LongMultiDouble(objRect.top, 1.4);
			objRect.bottom = LongMultiDouble(objRect.bottom, 1.4);
		}
	}

	drawRect.SetRect(tmpCenterPoint.x - drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y - drawInfo.drawRect.CenterPoint().y,
		tmpCenterPoint.x + drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y + drawInfo.drawRect.CenterPoint().y);

	checkRect = drawRect;
	long xGap = centerPoint.x - drawInfo.devRect.CenterPoint().x;
	long yGap = centerPoint.y - drawInfo.devRect.CenterPoint().y;

	if (xGap < 0)
		xGap = -xGap;
	if (yGap < 0)
		yGap = -yGap;

	xGap = (long)(4096. * xGap / 800.);
	yGap = (long)(4096. * yGap / 600.);

	checkRect.left -= xGap;
	checkRect.top -= yGap;
	checkRect.right += xGap;
	checkRect.bottom += yGap;

	if (!IsDrawObject(checkRect, objRect, drawRect))
		return false;

	if (g_tmpPointCount < pData->header.pointCount)
		g_tmpPointCount = pData->header.pointCount;
	memset(GlDrawBuffer, 0, sizeof(PointF) * MAX_DRAW_POINT_COUNT);
	for (nIdx = 0; nIdx < pData->header.pointCount; nIdx++)
	{
		inPoint = pData->pointList[nIdx];

		if (drawInfo.logicalLevel < 4)
		{
			inPoint.x <<= drawInfo.logicalLevel;
			inPoint.y <<= drawInfo.logicalLevel;
		}
		else
		{
			inPoint.x <<= (drawInfo.logicalLevel - 1);
			inPoint.y <<= (drawInfo.logicalLevel - 1);
			if (drawInfo.logicalLevel == 4)
			{
				inPoint.x = LongMultiDouble(inPoint.x, 1.4);
				inPoint.y = LongMultiDouble(inPoint.y, 1.4);
			}
		}

		inPoint.x -= drawRect.left;
		inPoint.y -= drawRect.top;


		outPoint.x = (long)((800. / 4096.) * inPoint.x);
		outPoint.y = (long)((600. / 4096.) * inPoint.y);
		outPoint.y = drawInfo.devRect.bottom - outPoint.y;

		outPoint.x = outPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
		outPoint.y = outPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

		if (drawInfo.headingUpMode == (long)1)
		{
			GlDrawBuffer[nIdx] = Rotate(outPoint, centerPoint, (long)angle).Point2PointF();
		}
		else
		{
			GlDrawBuffer[nIdx] = outPoint.Point2PointF();
		}

		g_TotalPointCount++;
	}

	if (designInfo->_line[drawInfo.dayNightMode].type == DESIGN_CONST::DRAW_TYPE::LINE_TYPE::NULLPEN)//Null Pointer Dereference
		isNullPen = true;
	else {
		drawPen.SetColor(colorConverter(designInfo->_line[drawInfo.dayNightMode].color));
		drawPen.SetWidth(designInfo->_line[drawInfo.dayNightMode].width);
		drawPen.SetDashStyle(designInfo->_line[drawInfo.dayNightMode].type);
	}

	int cntPoint = pData->header.textCount;
	graphics->DrawPolygon(&drawPen, GlDrawBuffer, cntPoint);
	return true;
}

long CMapDrawEngine::DrawPOI(_MapRecord* pData, double angle)
{
	Rect		drawRect;
	Rect		checkRect;
	Rect		objRect;
	Rect		rectBuffer;
	Point		centerPoint;
	Point		outPoint;
	Point		inPoint;
	Point		tmpCenterPoint = drawInfo.mapCenterPos4096;

	Rect		textRect;
	std::string		FieldValue;
	std::string		AddFieldValue;

	wchar_t		wBuffer[32];

	memset(&wBuffer, 0, sizeof(wBuffer));

	// Multibyte to Widechar
#if	defined(_UNICODE)
	FieldValue = pData->header.textData;
	AddFieldValue = pData->header.textData2;
#else
	// FieldValue.Format("%s", pData->header.textData);
	// AddFieldValue.Format("%s", pData->header.textData2);
#endif

	centerPoint = drawInfo.devCenterPos;

	inPoint = pData->pointList[0];

	if (drawInfo.logicalLevel < 4)
	{
		tmpCenterPoint.x <<= drawInfo.logicalLevel;
		tmpCenterPoint.y <<= drawInfo.logicalLevel;

		inPoint.x <<= drawInfo.logicalLevel;
		inPoint.y <<= drawInfo.logicalLevel;
	}
	else
	{
		tmpCenterPoint.x <<= (drawInfo.logicalLevel - 1);
		tmpCenterPoint.y <<= (drawInfo.logicalLevel - 1);

		inPoint.x <<= (drawInfo.logicalLevel - 1);
		inPoint.y <<= (drawInfo.logicalLevel - 1);

		if (drawInfo.logicalLevel == 4)
		{
			tmpCenterPoint.x = LongMultiDouble(tmpCenterPoint.x, 1.4);
			tmpCenterPoint.y = LongMultiDouble(tmpCenterPoint.y, 1.4);

			inPoint.x = LongMultiDouble(inPoint.x, 1.4);
			inPoint.y = LongMultiDouble(inPoint.y, 1.4);
		}
	}

	objRect.SetRect(inPoint.x - 1, inPoint.y - 1, inPoint.x + 1, inPoint.y + 1);

	drawRect.SetRect(tmpCenterPoint.x - drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y - drawInfo.drawRect.CenterPoint().y,
		tmpCenterPoint.x + drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y + drawInfo.drawRect.CenterPoint().y);

	checkRect = drawRect;
	if (drawInfo.headingUpMode == (long)1)
	{
		checkRect = GetBoundaryRect(drawRect, (long)angle);
		objRect = GetBoundaryRect(objRect, (long)angle);
	}

	if (!rectBuffer.IntersectRect(&checkRect, &objRect))
	{
		return false;
	}

	inPoint.x -= drawRect.left;
	inPoint.y -= drawRect.top;

	outPoint.x = (long)((800. / 4096.) * inPoint.x);
	outPoint.y = (long)((600. / 4096.) * inPoint.y);
	outPoint.y = drawInfo.devRect.bottom - outPoint.y;

	outPoint.x = outPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
	outPoint.y = outPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

	if (drawInfo.headingUpMode == (long)1)
	{
		GlDrawBuffer[0] = Rotate(outPoint, centerPoint, (long)angle).Point2PointF();
	}
	else
	{
		GlDrawBuffer[0] = outPoint.Point2PointF();
	}

	Brush textBrush(GREEN_MAP_CONST::MAP_GEN_TEXT_COLOR[0]);

	if (pData->header.textCount == 2)
	{
		textRect.left = GlDrawBuffer[0].X - 1;
		textRect.right = GlDrawBuffer[0].X + 1;
		textRect.top = GlDrawBuffer[0].Y - 1;
		textRect.bottom = GlDrawBuffer[0].Y + 1;
		graphics->DrawString(FieldValue.c_str(), -1, &m_MapFont, textRect.TopLeft().Point2PointF(), &textBrush);

		textRect.left = GlDrawBuffer[0].X - 1;
		textRect.right = GlDrawBuffer[0].X + 1;
		textRect.top = GlDrawBuffer[0].Y + 1;
		textRect.bottom = GlDrawBuffer[0].Y + 1;
		graphics->DrawString(AddFieldValue.c_str(), -1, &m_MapFont, textRect.TopLeft().Point2PointF(), &textBrush);
	}
	else
	{
		textRect.left = GlDrawBuffer[0].X - 1;
		textRect.right = GlDrawBuffer[0].X + 1;
		textRect.top = GlDrawBuffer[0].Y - 1;
		textRect.bottom = GlDrawBuffer[0].Y + 1;
		graphics->DrawString(FieldValue.c_str(), -1, &m_MapFont, textRect.TopLeft().Point2PointF(), &textBrush);

	}

	g_TotalPointCount++;


	return true;
}

long CMapDrawEngine::DrawBackground()
{
	//HDC tmpDC = CreateCompatibleDC(hDC);

	//DeleteDC(tmpDC);
	return true;
}

long CMapDrawEngine::DrawOutLineText(Rect textRect, std::string textString, Color inColor, Color outColor)
{
	Rect		tmpRect;
	long		OutLineGap = 2;
	Color		oldTextColor;


	if (inColor.r != outColor.r && inColor.g != outColor.g && inColor.b != outColor.b)
	{
		Brush textBrush(outColor);
		tmpRect = Rect(textRect.left - OutLineGap, textRect.top, textRect.right - OutLineGap, textRect.bottom);
		graphics->DrawString(textString.c_str(), -1, &m_MapFont, tmpRect.TopLeft().Point2PointF(), &textBrush);
		tmpRect = Rect(textRect.left + OutLineGap, textRect.top, textRect.right + OutLineGap, textRect.bottom);
		graphics->DrawString(textString.c_str(), -1, &m_MapFont, tmpRect.TopLeft().Point2PointF(), &textBrush);
		tmpRect = Rect(textRect.left, textRect.top - OutLineGap, textRect.right, textRect.bottom - OutLineGap);
		graphics->DrawString(textString.c_str(), -1, &m_MapFont, tmpRect.TopLeft().Point2PointF(), &textBrush);
		tmpRect = Rect(textRect.left, textRect.top + OutLineGap, textRect.right, textRect.bottom + OutLineGap);
		graphics->DrawString(textString.c_str(), -1, &m_MapFont, tmpRect.TopLeft().Point2PointF(), &textBrush);
	}

	//SetTextColor(hDC, inColor);
	Brush bb(inColor);
	graphics->DrawString(textString.c_str(), -1, &m_MapFont, tmpRect.TopLeft().Point2PointF(), &bb);
	return true;
}

long CMapDrawEngine::DrawCarImage()
{
	long	currentAngle = 360 - drawInfo.mapAngle;
	long	imageIndex = 0;
	long	imageXPos = 0;
	Point	centerPoint = drawInfo.devCenterPos;
	Point	drawPoint = drawInfo.devCenterPos;
	// long	symbolWidth = carImageInfo.bmWidth / 36;

	currentAngle %= 360;

	//SelectObject(tempDC, carImage);

	if (drawInfo.headingUpMode == (long)1)
	{
		if (1 == GREEN_MAP_CONST::MAP_MODE_PANNING::MODE_PANNING)
		{
			drawPoint = WorldToDevice(carPos);
			drawPoint = Rotate(drawPoint, centerPoint, drawInfo.mapAngle);
			currentAngle += drawInfo.mapAngle;
			currentAngle %= 360;
			imageIndex = currentAngle / 10;
		}
	}
	else
	{
		if (1 == GREEN_MAP_CONST::MAP_MODE_PANNING::MODE_PANNING)
		{
			drawPoint = WorldToDevice(carPos);
		}
		imageIndex = currentAngle / 10;
	}

	drawPoint.x -= 19;
	drawPoint.y -= 19;
	/*imageXPos = symbolWidth * imageIndex;*/

	//TransparentBlt(hDC, drawPoint.x, drawPoint.y, symbolWidth, carImageInfo.bmHeight,
		//tempDC, imageXPos, 0, symbolWidth, carImageInfo.bmHeight, RGB(255, 0, 255));

	return true;
}

long CMapDrawEngine::DrawSymbol(_dPoint mapPoint, Image img, std::string text)
{
	Point	drawPoint;
	Rect	checkRect = drawInfo.devRect;
	Point	centerPoint = drawInfo.devCenterPos;

	drawPoint = WorldToDevice(mapPoint);
	if (drawInfo.headingUpMode == (long)1)
	{
		drawPoint = Rotate(drawPoint, centerPoint, drawInfo.mapAngle);
	}

	checkRect.left -= 100;
	checkRect.right += 100;
	checkRect.top -= 100;
	checkRect.bottom += 100;

	if (checkRect.PtInRect(drawPoint) != false)
	{
		//SelectObject(tempDC, img);
		//TransparentBlt(hDC, drawPoint.x - gapX, drawPoint.y - gapY, imgInfo.bmWidth, imgInfo.bmHeight,
			//tempDC, 0, 0, imgInfo.bmWidth, imgInfo.bmHeight, RGB(255, 0, 255));
		//drawImage �ϴ� ��Ʈ��
		if (text.length() > 0)
		{
			Rect textRect = Rect(drawPoint.x - 100, drawPoint.y - 30, drawPoint.x + 100, drawPoint.y);
			Brush textBrush(GREEN_MAP_CONST::MAP_GEN_TEXT_COLOR[drawInfo.dayNightMode]);
			graphics->DrawString(text.c_str(), -1, &m_MapFont, textRect.TopLeft().Point2PointF(), &textBrush);
		}
	}

	return true;
}

long CMapDrawEngine::DrawSymbol(long staNum, long symbolType, _dPoint mapPoint, Color color, long lineSize, long angle, bool isTooMsn)
{
	Point	drawPoint;
	Rect	checkRect = drawInfo.devRect;
	Point	centerPoint = drawInfo.devCenterPos;

	drawPoint = WorldToDevice(mapPoint);
	if (drawInfo.headingUpMode == (long)1)
	{
		drawPoint = Rotate(drawPoint, centerPoint, drawInfo.mapAngle);
	}

	checkRect.left -= 100;
	checkRect.right += 100;
	checkRect.top -= 100;
	checkRect.bottom += 100;

	if (checkRect.PtInRect(drawPoint) != false)
	{
		DrawSymbol(staNum, symbolType, drawPoint, color, lineSize, angle, isTooMsn);
	}

	return true;
}

long CMapDrawEngine::DrawSymbol(long staNum, long symbolType, Point centerPoint, Color color, long lineSize, long angle, bool isTooMsn)
{
	Point	drawPoint;
	Point	symbolCenter;
	long	tmpIndex = 0;
	Pen     linePen(Color(0, 0, 0, 0));
	linePen.SetWidth(lineSize);
	linePen.SetColor(color);
	Pen		backPen(Color(0, 0, 0, 0));
	backPen.SetWidth(lineSize + 2);
	backPen.SetColor(GREEN_MAP_CONST::WHITE_COLOR);

	symbolCenter.x = MAP_DRAW_ENGINE_CONST::SYMBOL_SIZE[symbolType].x / 2;
	symbolCenter.y = MAP_DRAW_ENGINE_CONST::SYMBOL_SIZE[symbolType].y / 2;

	drawPoint.x = centerPoint.x - symbolCenter.x;
	drawPoint.y = centerPoint.y - symbolCenter.y;
	for (tmpIndex = 0; tmpIndex < MAP_DRAW_ENGINE_CONST::SYMBOL_POINT_COUNT[symbolType]; tmpIndex++)
	{
		GlDrawBuffer[tmpIndex].X = drawPoint.x + MAP_DRAW_ENGINE_CONST::SYMBOL_DATA[symbolType][tmpIndex].x;
		GlDrawBuffer[tmpIndex].Y = drawPoint.y + MAP_DRAW_ENGINE_CONST::SYMBOL_DATA[symbolType][tmpIndex].y;
	}

	if ((symbolType == MAP_DRAW_ENGINE_CONST::SYMBOL_TYPE::LAUNCH) || (symbolType == MAP_DRAW_ENGINE_CONST::SYMBOL_TYPE::TARGET))
	{
		Point	anglePoint;
		anglePoint = Rotate(MAP_DRAW_ENGINE_CONST::SYMBOL_DATA[symbolType][tmpIndex], symbolCenter, angle);
		if (drawInfo.headingUpMode == (long)1)
			anglePoint = Rotate(anglePoint, symbolCenter, drawInfo.mapAngle);

		GlDrawBuffer[tmpIndex].X = drawPoint.x + anglePoint.x;
		GlDrawBuffer[tmpIndex].Y = drawPoint.y + anglePoint.y;
		GlDrawBuffer[tmpIndex + 1].X = drawPoint.x + symbolCenter.x;
		GlDrawBuffer[tmpIndex + 1].Y = drawPoint.y + symbolCenter.y;
	}

	if ((symbolType != MAP_DRAW_ENGINE_CONST::SYMBOL_TYPE::TARGET) || (staNum == 999))
		graphics->DrawPolygon(&linePen, GlDrawBuffer, MAP_DRAW_ENGINE_CONST::SYMBOL_POINT_COUNT[symbolType]);

	if ((isTooMsn == false) && ((symbolType == MAP_DRAW_ENGINE_CONST::SYMBOL_TYPE::LAUNCH) || (symbolType == MAP_DRAW_ENGINE_CONST::SYMBOL_TYPE::TARGET)))
	{
		if (staNum == 999) {
			graphics->DrawPolygon(&linePen, &GlDrawBuffer[MAP_DRAW_ENGINE_CONST::SYMBOL_POINT_COUNT[symbolType]], 2);
		}
	}

	graphics->DrawPolygon(&linePen, GlDrawBuffer, MAP_DRAW_ENGINE_CONST::SYMBOL_POINT_COUNT[symbolType]);

	if ((isTooMsn == false) && ((symbolType == MAP_DRAW_ENGINE_CONST::SYMBOL_TYPE::LAUNCH) || (symbolType == MAP_DRAW_ENGINE_CONST::SYMBOL_TYPE::TARGET)))
		graphics->DrawPolygon(&linePen, &GlDrawBuffer[MAP_DRAW_ENGINE_CONST::SYMBOL_POINT_COUNT[symbolType]], 2);

	if ((symbolType == MAP_DRAW_ENGINE_CONST::SYMBOL_TYPE::TARGET) && (staNum == 999))
	{
		Rect textRect;
		std::string textString;

		//textString.Format(L"#%02d", CDataComm::GetCurStaionByAircraftIndex(GlAppState.indexOfSelectStation)); //org
		//Modified by eung32 20120223
		if (1 == APP_STATE_CONST::AIRCRAFT_TYPE::TYPE_F15S)
		{
			if (CDataComm::GetCurStaionByAircraftIndex(999) == 4)
			{
				textString = "# L";
			}
			else if (CDataComm::GetCurStaionByAircraftIndex(999) == 6)
			{
				textString = "# R";
			}
			else
			{
				//textString.Format(L"#%02d");
				//textString = std::format("#{:2}", CDataComm::GetCurStaionByAircraftIndex(GlAppState.indexOfSelectStation));
			}

		}
		else
		{
			//textString.Format(L"#%02d", CDataComm::GetCurStaionByAircraftIndex(GlAppState.indexOfSelectStation));
		}
		//end modify

		textRect.left = centerPoint.x - 52;
		textRect.right = centerPoint.x - 20;
		textRect.top = centerPoint.y - 10;
		textRect.bottom = centerPoint.y + 10;
		DrawOutLineText(textRect, textString, GREEN_MAP_CONST::RED_COLOR, GREEN_MAP_CONST::WHITE_COLOR);
	}

	return true;
}

long CMapDrawEngine::DrawHSI()
{
	long		circleRadius = 0;
	long		circleRadiusFactor = 30;
	Color	drawColor;
	Color	backDrawColor;

	if (drawInfo.dayNightMode == GREEN_MAP_CONST::MAP_MODE_DAYNIGHT::MAP_MODE_DAY)
	{
		drawColor = Color(255, 0, 0, 0);
		backDrawColor = Color(255, 255, 255, 255);
	}
	else
	{
		drawColor = Color(255, 29, 299, 29);
		backDrawColor = Color(255, 0, 0, 0);
	}

	Brush tmpBrush(Color(0, 0, 0, 0));
	Pen	tmpPen(drawColor, 3, PS_SOLID);
	Pen	tmpBackPen(backDrawColor, 7, PS_SOLID);


	double	angle = 0.0;
	double	tmpAngle = 0.0;
	long	angleIdx = 0;

	Point	inLine[2];
	Point	outLineD[2];
	Point outLine[2];
	Point	centerPoint = drawInfo.devCenterPos;;

	std::string textString;
	Rect	textRect;
	Rect	textBackRect;

	Color	oldTextColor;

	circleRadius = centerPoint.y - 291 - circleRadiusFactor;

	inLine[0].x = centerPoint.x;
	inLine[0].y = centerPoint.y - circleRadius;
	inLine[1].x = centerPoint.x;
	inLine[1].y = inLine[0].y + 10;


	for (angleIdx = 0; angleIdx < 36; angleIdx++)
	{
		tmpAngle = angle + drawInfo.mapAngle;
		if (tmpAngle >= 360.)
			tmpAngle -= 360.;

		outLineD[0] = Rotate(inLine[0], centerPoint, (long)tmpAngle);
		outLine[0].x = (long)outLineD[0].x;
		outLine[0].y = (long)outLineD[0].y;
		outLineD[1] = Rotate(inLine[1], centerPoint, (long)tmpAngle);
		outLine[1].x = (long)outLineD[1].x;
		outLine[1].y = (long)outLineD[1].y;

		graphics->DrawLine(&tmpBackPen, outLine[0].Point2PointF(), outLine[1].Point2PointF());
		graphics->DrawLine(&tmpPen, outLine[0].Point2PointF(), outLine[1].Point2PointF());

		if (angleIdx == 0)
		{
			textString = "N";
		}
		else if (angleIdx == 9)
		{
			textString = "E";
		}
		else if (angleIdx == 18)
		{
			textString = "S";
		}
		else if (angleIdx == 27)
		{
			textString = "W";
		}
		else
		{
			tmpAngle = angle / 10.;
			textString = tmpAngle;
		}
		textRect.left = outLine[1].x - 15;
		textRect.right = outLine[1].x + 15;
		textRect.top = outLine[1].y;
		textRect.bottom = outLine[1].y + 30;

		Brush bb(backDrawColor);
		textBackRect = textRect;
		textBackRect.left -= 2;
		textBackRect.right -= 2;
		graphics->DrawString(textString.c_str(), -1, &m_MapFont, textBackRect.TopLeft().Point2PointF(), &bb);
		textBackRect = textRect;
		textBackRect.left += 2;
		textBackRect.right += 2;
		graphics->DrawString(textString.c_str(), -1, &m_MapFont, textBackRect.TopLeft().Point2PointF(), &bb);
		textBackRect = textRect;
		textBackRect.top -= 2;
		textBackRect.bottom -= 2;
		graphics->DrawString(textString.c_str(), -1, &m_MapFont, textBackRect.TopLeft().Point2PointF(), &bb);
		textBackRect = textRect;
		textBackRect.top += 2;
		textBackRect.bottom += 2;
		graphics->DrawString(textString.c_str(), -1, &m_MapFont, textBackRect.TopLeft().Point2PointF(), &bb);


		Brush tb(drawColor);
		graphics->DrawString(textString.c_str(), -1, &m_MapFont, textRect.TopLeft().Point2PointF(), &tb);

		angle += 10.0;
		if (angle > 360.)
			angle -= 360.;
	}


	// Out Line
	Rect eRec(centerPoint.x - circleRadius, centerPoint.y - circleRadius,
		centerPoint.x + circleRadius, centerPoint.y + circleRadius);
	graphics->DrawEllipse(&tmpBackPen, eRec.Rect2RectF());

	Rect erec2(centerPoint.x - circleRadius, centerPoint.y - circleRadius,
		centerPoint.x + circleRadius, centerPoint.y + circleRadius);
	graphics->DrawEllipse(&tmpPen, erec2.Rect2RectF());

	//SelectObject(tempDC, arrowHSI[drawInfo.dayNightMode]);
	//TransparentBlt(hDC, centerPoint.x - 25, centerPoint.y - circleRadius + 25,
		//arrowHSIInfo[drawInfo.dayNightMode].bmWidth, arrowHSIInfo[drawInfo.dayNightMode].bmHeight,
		//tempDC, 0, 0, arrowHSIInfo[drawInfo.dayNightMode].bmWidth, arrowHSIInfo[drawInfo.dayNightMode].bmHeight, RGB(255, 0, 255));
	//drawimge �ϴ� ��Ʈ��
	return true;
}

long CMapDrawEngine::DrawGuideLine(_dPoint basePoint, _dPoint targetPoint, long lineType, long lineSize, Color lineColor, Color BackColor)
{
	Pen	tmpPen(Color(0, 0, 0, 0));
	Pen	backPen(Color(0, 0, 0, 0));
	Point	drawBuffer[4];
	Point	centerPoint = drawInfo.devCenterPos;

	memset(&drawBuffer, 0, sizeof(drawBuffer));
	tmpPen.SetDashStyle(lineType);
	tmpPen.SetWidth(lineSize);
	tmpPen.SetColor(lineColor);
	backPen.SetDashStyle(0);
	backPen.SetWidth(lineSize - 4);
	backPen.SetColor(BackColor);


	drawBuffer[0] = WorldToDevice(basePoint);
	drawBuffer[1] = WorldToDevice(targetPoint);
	if (drawInfo.headingUpMode == (long)1)
	{
		drawBuffer[0] = Rotate(drawBuffer[0], centerPoint, drawInfo.mapAngle);
		drawBuffer[1] = Rotate(drawBuffer[1], centerPoint, drawInfo.mapAngle);
	}


	graphics->DrawLine(&backPen, drawBuffer[0].Point2PointF(), drawBuffer[1].Point2PointF());
	graphics->DrawLine(&tmpPen, drawBuffer[0].Point2PointF(), drawBuffer[1].Point2PointF());
	return true;
}

long CMapDrawEngine::DrawRangeCircle(_dPoint inPoint, double distance, long lineType, long lineSize, long backLineSize, Color lineColor, Color BackColor, std::string text)
{
	Rect	drawRect;
	long	gapValue = 0;
	long	gapValue2 = 0;

	Point IIPoint;
	_dPoint UUPoint;
	Point basePoint;
	_dPoint utmCenterPos;
	Point	centerPoint = drawInfo.devCenterPos;
	Pen	tmpPen(lineColor, lineSize, lineType);
	Pen	tmpBackPen(BackColor, backLineSize, lineType);
	Brush tmpBrush(Color(0, 0, 0, 0));

	// IZLAR Draw
	memset(GlDrawBuffer, 0, sizeof(GlDrawBuffer));
	GetUTM(inPoint, utmCenterPos);

	// MinRadius Draw
	UUPoint.x = utmCenterPos.x - distance;
	UUPoint.y = utmCenterPos.y - distance;
	IIPoint = WorldToDeviceUTM(utmCenterPos);
	basePoint = WorldToDeviceUTM(UUPoint);

	gapValue = basePoint.x - IIPoint.x;
	if (gapValue < 0)
		gapValue = -gapValue;

	gapValue2 = basePoint.y - IIPoint.y;
	if (gapValue2 < 0)
		gapValue2 = -gapValue2;

	if (drawInfo.headingUpMode == (long)1)
		basePoint = Rotate(IIPoint, centerPoint, drawInfo.mapAngle);
	else
		basePoint = IIPoint;

	drawRect.left = basePoint.x - gapValue;
	drawRect.top = basePoint.y - gapValue2;
	drawRect.right = basePoint.x + gapValue;
	drawRect.bottom = basePoint.y + gapValue2;

	graphics->DrawEllipse(&tmpPen, drawRect.Rect2RectF());
	if (text.length() > 0)
	{
		Brush textBrush(GREEN_MAP_CONST::MAP_GEN_TEXT_COLOR[drawInfo.dayNightMode]);
		graphics->DrawString(text.c_str(), -1, &m_MapFont, drawRect.TopLeft().Point2PointF(), &textBrush);
	}


	return true;
}

long CMapDrawEngine::DrawListLine(_dPoint* inPointList, long pointCount, long lineType, long lineSize, long backLineSize, Color lineColor, Color BackColor, std::string text)
{
	long	index = 0;
	Point	centerPoint = drawInfo.devCenterPos;
	Pen	tmpPen(lineColor, lineSize, lineType);
	Pen	tmpBackPen(BackColor, backLineSize, lineType);
	Rect	textRect = Rect(9999, 9999, 0, 0);

	if ((pointCount < 2) || (inPointList == NULL))
		return false;

	memset(GlDrawBuffer, 0, sizeof(GlDrawBuffer));

	for (index = 0; index < pointCount; index++)
	{
		GlDrawBuffer[index] = WorldToDevice(inPointList[index]).Point2PointF();
		if (drawInfo.headingUpMode == (long)1)
		{
			Point pp;
			pp.x = GlDrawBuffer[index].X;
			pp.y = GlDrawBuffer[index].Y;
			GlDrawBuffer[index] = Rotate(pp, centerPoint, drawInfo.mapAngle).Point2PointF();
		}

		if (GlDrawBuffer[index].X < textRect.left)
			textRect.left = GlDrawBuffer[index].X;
		if (GlDrawBuffer[index].Y < textRect.top)
			textRect.top = GlDrawBuffer[index].Y;
		if (GlDrawBuffer[index].X > textRect.right)
			textRect.right = GlDrawBuffer[index].X;
		if (GlDrawBuffer[index].Y > textRect.bottom)
			textRect.bottom = GlDrawBuffer[index].Y;
	}

	if (pointCount >= 2)	// 20120115
	{
		if ((GlDrawBuffer[0].X != GlDrawBuffer[pointCount - 1].X) || (GlDrawBuffer[0].Y != GlDrawBuffer[pointCount - 1].Y))
		{
			GlDrawBuffer[pointCount] = GlDrawBuffer[0];
			pointCount++;
		}
		graphics->DrawPolygon(&tmpPen, GlDrawBuffer, pointCount);
		if (text.length() > 0);
		{
			Brush tbtb(GREEN_MAP_CONST::MAP_GEN_TEXT_COLOR[drawInfo.dayNightMode]);
			graphics->DrawString(text.c_str(), -1, &m_MapFont, textRect.TopLeft().Point2PointF(), &tbtb);
		}
	}

	// 20120115 Number Text Add
	std::string numString;
	for (index = 0; index < pointCount - 1; index++)
	{
		numString = index + 1;
		textRect.left = GlDrawBuffer[index].X - 15;
		textRect.right = GlDrawBuffer[index].X + 15;
		textRect.top = GlDrawBuffer[index].Y - 15;
		textRect.bottom = GlDrawBuffer[index].Y + 15;
		DrawOutLineText(textRect, numString, GREEN_MAP_CONST::BLACK_COLOR, GREEN_MAP_CONST::WHITE_COLOR);
	}


	return true;
}

Point CMapDrawEngine::Rotate(Point inPoint, Point centerPoint, long angle)
{
	Point outPoint;

	angle %= 360;

	long cosValue = m_CosValue[angle];
	long sinValue = m_SinValue[angle];

	inPoint.x -= centerPoint.x;
	inPoint.y -= centerPoint.y;

	outPoint.x = (inPoint.x * cosValue - inPoint.y * sinValue) >> 14;
	outPoint.y = (inPoint.y * cosValue + inPoint.x * sinValue) >> 14;

	outPoint.x += centerPoint.x;
	outPoint.y += centerPoint.y;

	return outPoint;
}

_dPoint CMapDrawEngine::RotateDouble(_dPoint inPoint, _dPoint centerPoint, long angle)
{
	_dPoint outPoint;

	angle %= 360;

	long dValue = 1;
	dValue = dValue << 14;

	long cosValue = m_CosValue[angle];
	long sinValue = m_SinValue[angle];

	inPoint.x -= centerPoint.x;
	inPoint.y -= centerPoint.y;

	outPoint.x = (inPoint.x * cosValue - inPoint.y * sinValue) / (double)dValue;
	outPoint.y = (inPoint.y * cosValue + inPoint.x * sinValue) / (double)dValue;

	outPoint.x += centerPoint.x;
	outPoint.y += centerPoint.y;

	return outPoint;
}

Point CMapDrawEngine::WorldToDeviceUTM(const _dPoint _inPoint)
{
	_LatLonDMS	latlonDMS;
	Point	retPoint;
	_dPoint calcuPoint;
	_dPoint factorValue;
	long	scale = 1;

	/* remarked by swkang in Dec. 22nd, 2015 : for moving the init point from 52 to 40 */
	//GetUTM2KW(52, _inPoint, latlonDMS);
	GetUTM2KW(40, _inPoint, latlonDMS);

	calcuPoint.x = latlonDMS.LonDo + (latlonDMS.LonBun / 60.) + (latlonDMS.LonCho / 3600.);
	calcuPoint.y = latlonDMS.LatDo + (latlonDMS.LatBun / 60.) + (latlonDMS.LatCho / 3600.);

	double	xPos = ((calcuPoint.x * 28800.) - drawInfo.mapCenterPos.x);
	double	yPos = ((calcuPoint.y * 28800.) - drawInfo.mapCenterPos.y);

	long	level = _mapFactorInfo.GetTableLevel(0);
	long	xGap = _mapFactorInfo._levelGapTable[GREEN_MAP_CONST::MAP_POSITION_INDEX::LONGITUDE][level];
	long	yGap = _mapFactorInfo._levelGapTable[GREEN_MAP_CONST::MAP_POSITION_INDEX::LATITUDE][level];

	factorValue.x = xPos * 800. / xGap;
	factorValue.y = yPos * 600. / yGap;

	if (drawInfo.logicalLevel < 4)
		scale <<= drawInfo.logicalLevel;
	else
	{
		scale <<= (drawInfo.logicalLevel - 1);
		if (drawInfo.logicalLevel == 4)
			scale = LongMultiDouble(scale, 1.4);
	}

	factorValue.x = factorValue.x * scale;
	factorValue.y = factorValue.y * scale;
	retPoint.x = drawInfo.devCenterPos.x + (long)(factorValue.x);
	retPoint.y = drawInfo.devCenterPos.y - (long)(factorValue.y);

	return retPoint;
}

Point CMapDrawEngine::WorldToDevice(const _dPoint _inPoint)
{
	Point	retPoint;
	_dPoint factorValue;
	long	scale = 1;

	double	xPos = ((_inPoint.x * 28800.) - drawInfo.mapCenterPos.x);
	double	yPos = ((_inPoint.y * 28800.) - drawInfo.mapCenterPos.y);

	long	level = _mapFactorInfo.GetTableLevel(0);
	long	xGap = _mapFactorInfo._levelGapTable[GREEN_MAP_CONST::MAP_POSITION_INDEX::LONGITUDE][level];
	long	yGap = _mapFactorInfo._levelGapTable[GREEN_MAP_CONST::MAP_POSITION_INDEX::LATITUDE][level];

	factorValue.x = xPos * 800. / xGap;
	factorValue.y = yPos * 600. / yGap;

	if (drawInfo.logicalLevel < 4)
		scale <<= drawInfo.logicalLevel;
	else
	{
		scale <<= (drawInfo.logicalLevel - 1);
		if (drawInfo.logicalLevel == 4)
			scale = LongMultiDouble(scale, 1.4);
	}

	factorValue.x = factorValue.x * scale;
	factorValue.y = factorValue.y * scale;
	retPoint.x = drawInfo.devCenterPos.x + (long)(factorValue.x);
	retPoint.y = drawInfo.devCenterPos.y - (long)(factorValue.y);

	return retPoint;
}

_dPoint CMapDrawEngine::DeviceToWorld(const Point _inPoint)
{
	return DeviceToWorldMove(_inPoint, drawInfo.devCenterPos);
}

_dPoint CMapDrawEngine::DeviceToWorldMove(const Point _inPoint, Point centerPoint)
{
	_dPoint	retPoint;
	Point deltaPoint;
	_dPoint deltaMapPoint;
	Point mapCenterPoint = drawInfo.mapCenterPos4096;

	deltaPoint.x = centerPoint.x - _inPoint.x;
	deltaPoint.y = _inPoint.y - centerPoint.y;

	if (drawInfo.logicalLevel < 4)
	{
		deltaPoint.x >>= drawInfo.logicalLevel;
		deltaPoint.y >>= drawInfo.logicalLevel;
	}
	else
	{
		deltaPoint.x >>= (drawInfo.logicalLevel - 1);
		deltaPoint.y >>= (drawInfo.logicalLevel - 1);
		if (drawInfo.logicalLevel == 4)
		{
			deltaPoint.x = LongMultiDouble(deltaPoint.x, 1.4);
			deltaPoint.y = LongMultiDouble(deltaPoint.y, 1.4);
		}
	}


	deltaMapPoint.x = 4096.;
	deltaMapPoint.y = 4096.;

	deltaMapPoint.x = deltaPoint.x * deltaMapPoint.x / 800.;
	// changed by swkang in Jan. 20th, 2016 : 800 --> 600
	deltaMapPoint.y = deltaPoint.y * deltaMapPoint.y / 600.;

	mapCenterPoint.x -= (long)deltaMapPoint.x;
	mapCenterPoint.y -= (long)deltaMapPoint.y;

	retPoint.x = _mapFactorInfo._basePoint.x + (long)((double)mapCenterPoint.x /
		_mapFactorInfo._levelFactorTable[GREEN_MAP_CONST::MAP_POSITION_INDEX::LONGITUDE][_mapFactorInfo.GetTableLevel(0)]);
	retPoint.y = _mapFactorInfo._basePoint.y + (long)((double)mapCenterPoint.y /
		_mapFactorInfo._levelFactorTable[GREEN_MAP_CONST::MAP_POSITION_INDEX::LATITUDE][_mapFactorInfo.GetTableLevel(0)]);

	retPoint.x = retPoint.x / 28800.;/* converting into degree, 28800 =  3600 * 8 */
	retPoint.y = retPoint.y / 28800.;/* converting into degree, 28800 =  3600 * 8 */

	return retPoint;
}

long CMapDrawEngine::GetUTM(_dPoint inPoint, _dPoint& utmPoint, long param)
{
	_LatLonDMS	latlonDMS;
	double	tutmx = 0.;
	double	tutmy = 0.;
	double	slam = 0.;
	double	sphi = 0.;
	int		tmp_zone = 0;

	CAppLib::Coord_GetDMSbyDegree(inPoint, latlonDMS);
	slam = CAppLib::Coord_GetRadian(latlonDMS.LonDo, latlonDMS.LonBun, latlonDMS.LonCho);	// �浵
	sphi = CAppLib::Coord_GetRadian(latlonDMS.LatDo, latlonDMS.LatBun, latlonDMS.LatCho);	// ����

	CAppLib::Coord_Tawon2UTM(GREEN_MAP_CONST::MAP_COORD_TYPE::WGS_84_TYPE, sphi, slam, &m_BaseZone, &tutmy, &tutmx, 0);// if 0, calculate UTM Zone

	if (param == 0)
	{
		if (m_BaseZone == 52)
		{
			utmPoint.x = tutmx;
			utmPoint.y = tutmy;
		}
		else
		{
			tmp_zone = 40;
			CAppLib::Coord_Tawon2UTM(GREEN_MAP_CONST::MAP_COORD_TYPE::WGS_84_TYPE, sphi, slam, &tmp_zone, &tutmy, &tutmx, 1);// if 1, using assigned UTM Zone
			utmPoint.x = tutmx;
			utmPoint.y = tutmy;
		}
	}
	else
	{
		utmPoint.x = tutmx;
		utmPoint.y = tutmy;
	}
	return m_BaseZone;
}

long CMapDrawEngine::GetUTM2KW(long izone, _dPoint utmPoint, _LatLonDMS& latlonDMS)
{
	double sphi = 0.;
	double slam = 0.;

	CAppLib::Coord_UTM2Tawon(GREEN_MAP_CONST::MAP_COORD_TYPE::WGS_84_TYPE, &sphi, &slam, izone, utmPoint.y, utmPoint.x);
	CAppLib::Coord_GetDMS(sphi, latlonDMS.LatDo, latlonDMS.LatBun, latlonDMS.LatCho);
	CAppLib::Coord_GetDMS(slam, latlonDMS.LonDo, latlonDMS.LonBun, latlonDMS.LonCho);

	return true;
}

std::string CMapDrawEngine::GetUTM2MGRS(int zone, _dPoint utmPoint)
{
	return CAppLib::Coord_UTM2MGRS(GREEN_MAP_CONST::MAP_COORD_TYPE::WGS_84_TYPE, zone, utmPoint);
}

bool CMapDrawEngine::GetMGRS2UTM(std::string mgrs, _dPoint& utmPoint)
{
	return CAppLib::Coord_MGRS2UTM(mgrs, utmPoint);
}
