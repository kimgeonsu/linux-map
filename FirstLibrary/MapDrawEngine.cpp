#include "MapDataManager.h"
#include "MapDrawEngine.h"
#include "AppLibrary.h"

#include "MyType.h"

#define MAX_DRAW_POINT_COUNT	8192
PointF g_DrawBuffer[MAX_DRAW_POINT_COUNT];


CMapDrawEngine::CMapDrawEngine()
{
	Color color = Color(0, 0, 0);
	Color color2 = Color(128, 0, 0);
	m_NULLPEN = Pen(color, 1.0);
	m_NULLBRUSH = Brush(color, 1);
	m_BACKBRUSH = Brush(color2, 1);

	graphics = new Graphics("/dev/fb0");

	//LOGFONT		FontInfo;
	//memset(&FontInfo, 0, sizeof(LOGFONT));
	//FontInfo.lfHeight = 8;
	//FontInfo.lfWeight = 500;
	//FontInfo.lfCharSet = 1;
	//FontInfo.lfFaceName = "Tahoma";
	m_MapFont[0] = Font("fontName1", 8);

	/*FontInfo.lfHeight = 12;*/
	m_MapFont[1] = Font("fontName2", 12);


	m_BaseZone = 52;

	double radius;

	for (long angleIdx = 0; angleIdx < 360; angleIdx++)
	{
		radius = (double)(angleIdx * 3.141592653589793238462643383279502884197169399375105820974944592308 / 180.);
		m_CosValue[angleIdx] = (long)(cos(radius) * 10000);
		m_SinValue[angleIdx] = (long)(sin(radius) * 10000);
	}
}

CMapDrawEngine::~CMapDrawEngine()
{
	//GlReleaseHOBJ(&m_NULLPEN);
	//GlReleaseHOBJ(&m_NULLBRUSH);
	//GlReleaseHOBJ(&m_BACKBRUSH);
	//GlReleaseHOBJ(&m_MapFont[0]);
	//GlReleaseHOBJ(&m_MapFont[1]);
}

long CMapDrawEngine::Init()
{
	long mapTypeIdx = 0;
	mapDataManager.Init();

	return true;
}

long CMapDrawEngine::DrawMap()
{ 
	
	long	tmpFontSize = 0;
	long	nIdx = 0;
	Font	oldFont;
	/*graphics->FillRectangle(hDC, drawInfo.devRect, m_BACKBRUSH);*/
	RectF change = drawInfo.devRect.Rect2RectF();
	graphics->FillRectangle(&m_BACKBRUSH, change);

	if (drawInfo.logicalLevel == 0)
	{
		oldFont = m_MapFont[0];
	}
	else
	{
		oldFont = m_MapFont[1];
	}
	std::list<_MapRecord>::iterator pos = mapDataManager._drawData._drawDataList.begin();
	std::list<_MapRecord>::iterator eee = mapDataManager._drawData._drawDataList.end();
	
	_MapRecord pData;
	
	for (pos; pos != eee; pos++) {
		pData = *pos; 
		switch (pData.header.objType)
		{
		case 1:
			std::cout << "DrawPOI( " << drawInfo.mapAngle << ", " << nIdx << std::endl;
			DrawPOI(&pData, drawInfo.mapAngle, nIdx);
			break;
		case 3:
			// std::cout << "DrawPolyline(&pData, drawInfo.mapAngle, nIdx);\n";
			// DrawPolyline(&pData, drawInfo.mapAngle, nIdx);
			break;
		case 5:
			std::cout << "DrawPolygon(&pData, drawInfo.mapAngle, nIdx);\n";
			DrawPolygon(&pData, drawInfo.mapAngle, nIdx);
			break;
		default:
			break;
		}

	}

	//SelectObject(hDC, oldFont);

	Color red = Color(255, 0, 0);
	Brush testBrush = Brush(red, 1);
	Rect tmpRect;
	tmpRect.left = drawInfo.devCenterPos.x - 5;
	tmpRect.top = drawInfo.devCenterPos.y - 5;
	tmpRect.right = drawInfo.devCenterPos.x + 5;
	tmpRect.bottom = drawInfo.devCenterPos.y + 5;

	RectF Convert = tmpRect.Rect2RectF();
	graphics->FillRectangle(&testBrush, Convert);
	//GlReleaseHOBJ(&testBrush);
	return true;
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
	Point centerPoint = drawInfo.devCenterPos;

	inPoint[0] = Point(inRect.left, inRect.top);
	inPoint[1] = Point(inRect.right, inRect.top);
	inPoint[2] = Point(inRect.left, inRect.bottom);
	inPoint[3] = Point(inRect.right, inRect.bottom);

	for (index = 0; index < 4; index++) {
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

bool CMapDrawEngine::IsDrawObject(Rect drawRect, Rect objRect)
{
	Point	checkPoint;
	Rect	inRect = objRect;
	Rect	cmpRect = drawRect;
	if ((drawRect.Width() < objRect.Width()) || (drawRect.Height() < objRect.Height()))
	{
		inRect = drawRect;
		cmpRect = objRect;
	}

	checkPoint = inRect.TopLeft();
	if (cmpRect.PtInRect(checkPoint) == true)
		return true;

	checkPoint = inRect.TopLeft();
	if (cmpRect.PtInRect(checkPoint) == true)
		return true;

	checkPoint.x = inRect.right;
	checkPoint.y = inRect.top;
	if (cmpRect.PtInRect(checkPoint) == true)
		return true; 

	checkPoint.x = inRect.left;
	checkPoint.y = inRect.bottom;
	if (cmpRect.PtInRect(checkPoint) == true)
		return true;

	return false;
}

long CMapDrawEngine::DrawPolygon(_MapRecord* pData, double angle, long bufferIdx)
{
	// for intersect calculation..
	Rect		objRect(pData->header.boundaryRect);
	Rect		drawRect;
	Rect		checkRect;
	Rect		rectBuffer;
	Point		centerPoint;
	Point		outPoint;
	Point		inPoint;
	Point		textPoint;
	Rect		textRect;
	Point		tmpCenterPoint(drawInfo.mapCenterPos4096);
	long		nIdx = 0;

	Point		textSize;
	/*long		oldTextColor;*/

	std::string		textData;

	Brush		oldBrush;
	Brush		fillBrush;
	Pen		drawPen;
	Pen		oldPen;

	Font font = Font("포온트", 0);

	_DesignRecord* designInfo = mapDataManager._designRecordMng.GetRecordData(pData->header.designCode);

	centerPoint = drawInfo.devCenterPos;

	tmpCenterPoint.x <<= drawInfo.logicalLevel;
	tmpCenterPoint.y <<= drawInfo.logicalLevel;

	objRect.left <<= drawInfo.logicalLevel;
	objRect.right <<= drawInfo.logicalLevel;
	objRect.top <<= drawInfo.logicalLevel;
	objRect.bottom <<= drawInfo.logicalLevel;

	drawRect.SetRect(tmpCenterPoint.x - drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y - drawInfo.drawRect.CenterPoint().y,
		tmpCenterPoint.x + drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y + drawInfo.drawRect.CenterPoint().y);

	std::cout <<"디벙깅 1\n";

	textPoint = objRect.CenterPoint();
	checkRect = drawRect;
	long xGap = centerPoint.x - drawInfo.devRect.CenterPoint().x;
	long yGap = centerPoint.y - drawInfo.devRect.CenterPoint().y;

	if (xGap < 0)
		xGap = -xGap;
	if (yGap < 0)
		yGap = -yGap;

	xGap = (long)(4096. * xGap / 800.);
	yGap = (long)(4096. * yGap / 800.);
	checkRect.left -= xGap;
	checkRect.top -= yGap;
	checkRect.right += xGap;
	checkRect.bottom += yGap;

	std::cout <<"디벙깅 2\n";

	if (drawInfo.headingUpMode == 1)
	{
		std::cout<< "혹시 너? 11\n";
		objRect = GetBoundaryRect(objRect, (long)angle);
		std::cout<< "혹시 너? 22\n";
		checkRect = GetBoundaryRect(checkRect, (long)angle);
	}
	std::cout<< "혹시 너? 33\n";

	// Text Point Calculate
	// textData = pData->header.textData;
	std::cout<< "혹시 너? 44\n";
	if (!rectBuffer.IntersectRect(&checkRect, &objRect))
	{
		return false;
	}

	std::cout <<"디벙깅 3\n";

	memset(&g_DrawBuffer, 0, sizeof(PointF) * MAX_DRAW_POINT_COUNT);
	for (nIdx = 0; nIdx < pData->header.pointCount; nIdx++)
	{
		inPoint = pData->pointList[nIdx];

		inPoint.x <<= drawInfo.logicalLevel;
		inPoint.y <<= drawInfo.logicalLevel;

		inPoint.x -= drawRect.left;
		inPoint.y -= drawRect.top;

		outPoint.x = (long)((800. / 4096.) * inPoint.x);
		outPoint.y = (long)((800. / 4096.) * inPoint.y);
		outPoint.y = drawInfo.devRect.bottom - outPoint.y;

		outPoint.x = outPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
		outPoint.y = outPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

		if (drawInfo.headingUpMode == 1)
		{
			g_DrawBuffer[nIdx] = Rotate(outPoint, centerPoint, (long)angle).Point2PointF();
		}
		else
		{
			g_DrawBuffer[nIdx] = outPoint.Point2PointF();
		}
	}

	std::cout <<"디벙깅 4\n";

	if (designInfo != NULL)
	{
		if (designInfo->objType == (unsigned char)2)
		{
			Color color = Color(0, 256, 0);
			fillBrush = Brush(color);
			oldBrush = fillBrush;
		}
		else
		{
			oldBrush = m_NULLBRUSH;
		}

		if (designInfo->_line[drawInfo.dayNightMode].type == '5')
		{
			Color color = Color(256, 256, 256);
			drawPen = Pen(color, 0);
		}
		else
		{
			Color color = Color(0, 0, 0);
			drawPen = Pen(color, 1);
		}
		oldPen = drawPen;
	}
	else
	{
		oldBrush = m_NULLBRUSH;
	}
	std::cout <<"디벙깅 5\n";
	// graphics->DrawPolygon(&(drawPen), g_DrawBuffer, nIdx);
	std::cout <<"디벙깅 6\n";

	// Text Output
	if ((textData.length() > 0) && (designInfo != NULL))
	{
		std::cout << "textData가 문제인가? 1\n";
		textPoint.x -= drawRect.left;
		textPoint.y -= drawRect.top;

		textPoint.x = (long)((800. / 4096.) * textPoint.x);
		textPoint.y = (long)((800. / 4096.) * textPoint.y);
		textPoint.y = drawInfo.devRect.bottom - textPoint.y;
		std::cout << "textData가 문제인가? 2\n";

		textPoint.x = textPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
		textPoint.y = textPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

		// ������ϰ��
		if (drawInfo.headingUpMode == 1)
		{
			textPoint = Rotate(textPoint, centerPoint, (long)angle);
		}
		std::cout << "textData가 문제인가? 3\n";

		//GetTextExtentPoint(hDC, textData, textData.length(), &textSize);
		textSize.x += 4;
		textSize.y += 4;

		textRect.left = textPoint.x - (int)(textSize.x / 2) - 1;
		textRect.right = textPoint.x + (int)(textSize.x / 2) + 1;
		textRect.top = textPoint.y - (int)(textSize.y / 2) - 1;
		textRect.bottom = textPoint.y + (int)(textSize.y / 2) + 1;

		//oldTextColor = GetTextColor(hDC);
		// SetTextColor(hDC, RGB(150, 79, 223));
		//SetTextColor(hDC, designInfo->_fontStyle[drawInfo.dayNightMode].color);
		// PointF tmp;
		// tmp.X = textRect.TopLeft().x;
		// tmp.Y = textRect.TopLeft().y;
		std::cout << "textData가 문제인가? 4\n";
		
		// std::cout << textData.length() << std::endl;
		// graphics->DrawString(pData->header.textData, -1, &font, textPoint.Point2PointF(), &fillBrush);
		//SetTextColor(hDC, oldTextColor);
		std::cout << "textData가 문제인가? 5\n";

	}

	std::cout <<"디벙깅 7\n";

	//SelectObject(hDC, oldBrush);

	// if (designInfo != NULL)
	// {
	// 	SelectObject(hDC, oldPen);
	// 	if (designInfo->objType == 2)
	// 	{
	// 		GlReleaseHOBJ(&fillBrush);
	// 	}
	// 	GlReleaseHOBJ(&drawPen);
	// }

	std::cout <<"디벙깅 8\n";
	std::cout << pData->header.textData << std::endl;
// #if MAP_DISPLAY_DEBUG_MSG
// 	TRACE("POLYGON ==> mapType : %d, displayCode : %d\n", mapType, pData->header.code);
// #endif
	std::cout <<"디벙깅 9\n";

	return true;
}

long CMapDrawEngine::DrawPolyline(_MapRecord* pData, double angle, long bufferIdx)
{
	Rect		objRect = pData->header.boundaryRect;
	Rect		drawRect;
	Rect		checkRect;
	Rect		rectBuffer;
	Point		centerPoint;
	Point		outPoint;
	Point		inPoint;
	Point		tmpCenterPoint = drawInfo.mapCenterPos4096;
	long		nIdx = 0;
	Pen		drawPen;
	Pen		oldPen;
	_DesignRecord* designInfo = mapDataManager._designRecordMng.GetRecordData(pData->header.designCode);


	centerPoint = drawInfo.devCenterPos;

	tmpCenterPoint.x <<= drawInfo.logicalLevel;
	tmpCenterPoint.y <<= drawInfo.logicalLevel;

	objRect.left <<= drawInfo.logicalLevel;
	objRect.right <<= drawInfo.logicalLevel;
	objRect.top <<= drawInfo.logicalLevel;
	objRect.bottom <<= drawInfo.logicalLevel;

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
	yGap = (long)(4096. * yGap / 800.);
	checkRect.left -= xGap;
	checkRect.top -= yGap;
	checkRect.right += xGap;
	checkRect.bottom += yGap;

	if (drawInfo.headingUpMode == 1)
	{
		objRect = GetBoundaryRect(objRect, (long)angle);
		checkRect = GetBoundaryRect(checkRect, (long)angle);
	}


	if (!rectBuffer.IntersectRect(&checkRect, &objRect))
	{
		return false;
	}

	memset(&g_DrawBuffer, 0, sizeof(Point) * MAX_DRAW_POINT_COUNT);
	for (nIdx = 0; nIdx < pData->header.pointCount; nIdx++)
	{
		inPoint = pData->pointList[nIdx];

		inPoint.x <<= drawInfo.logicalLevel;
		inPoint.y <<= drawInfo.logicalLevel;

		inPoint.x -= drawRect.left;
		inPoint.y -= drawRect.top;


		outPoint.x = (long)((800. / 4096.) * inPoint.x);
		outPoint.y = (long)((800. / 4096.) * inPoint.y);
		outPoint.y = drawInfo.devRect.bottom - outPoint.y;

		outPoint.x = outPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
		outPoint.y = outPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

		PointF tmp;
		if (drawInfo.headingUpMode == 1)
		{
			g_DrawBuffer[nIdx] = Rotate(outPoint, centerPoint, (long)angle).Point2PointF();
			Point temp = Rotate(outPoint, centerPoint, (long)angle);
			tmp.X = temp.x;
			tmp.Y = temp.y;
			g_DrawBuffer[nIdx] = tmp;
		}
		else
		{
			g_DrawBuffer[nIdx] = outPoint.Point2PointF();
			tmp.X = outPoint.x;
			tmp.Y = outPoint.y;
			g_DrawBuffer[nIdx] = tmp;
		}
	}

	if (designInfo != NULL)
	{
		if (designInfo->_line[drawInfo.dayNightMode].type == 5)
		{
			Color color = Color(0, 0, 0);
			drawPen = Pen(color, 0);
		}
		else
		{
			//drawPen = CreatePen(designInfo->_line[drawInfo.dayNightMode].type, designInfo->_line[drawInfo.dayNightMode].width, designInfo->_line[drawInfo.dayNightMode].color);
			Color color = Color(256, 0, 0);
			drawPen = Pen(color, 1);
		}

		oldPen = drawPen;
	}

	graphics->DrawLines(&drawPen, g_DrawBuffer, pData->header.pointCount);
	for (int i = 0; i < 2; i++) {
		std:: cout << g_DrawBuffer[i].X << " " << g_DrawBuffer[i].Y << std::endl; 
	}

	if (designInfo != NULL)
	{
		//SelectObject(hDC, oldPen);
		//GlReleaseHOBJ(&drawPen);
	}


// #if MAP_DISPLAY_DEBUG_MSG
// 	TRACE("ARC ==> mapType : %d, displayCode : %d\n", mapType, pData->header.code);
// #endif
	return true;
}

long CMapDrawEngine::DrawPOI(_MapRecord* pData, double angle, long bufferIdx)
{
	Rect		drawRect;
	Rect		checkRect;
	Rect		objRect;
	Rect		rectBuffer;
	Point		centerPoint;
	Point		outPoint;
	Point		inPoint;
	Point		tmpCenterPoint = drawInfo.mapCenterPos4096;

	Point		textSize;
	Rect		textRect;
	std::string		FieldValue;
	//unsigned long	oldTextColor;

std::cout << "Step 1" << std::endl;

	Font font = Font("폰트폰트", 1);
	Brush fillBrush = Brush(Color(0, 0, 0));

	wchar_t		wBuffer[32];

	memset(&wBuffer, 0, sizeof(wBuffer));

	// Multibyte to Widechar
// #if	defined(_UNICODE)
// 	long		textLength;

// 	textLength = MultiByteToWideChar(CP_ACP, 0, pData->header.textData, (long)strlen(pData->header.textData), NULL, NULL);
// 	MultiByteToWideChar(CP_ACP, 0, pData->header.textData, (long)strlen(pData->header.textData), wBuffer, textLength);
// 	FieldValue.Format(L"%s", wBuffer);
// #else
// 	FieldValue = pData->header.textData;
// #endif

	centerPoint = drawInfo.devCenterPos;

	inPoint = pData->pointList[0];

	tmpCenterPoint.x <<= drawInfo.logicalLevel;
	tmpCenterPoint.y <<= drawInfo.logicalLevel;

	inPoint.x <<= drawInfo.logicalLevel;
	inPoint.y <<= drawInfo.logicalLevel;

	objRect.SetRect(inPoint.x - 1, inPoint.y - 1, inPoint.x + 1, inPoint.y + 1);

	drawRect.SetRect(tmpCenterPoint.x - drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y - drawInfo.drawRect.CenterPoint().y,
		tmpCenterPoint.x + drawInfo.drawRect.CenterPoint().x, tmpCenterPoint.y + drawInfo.drawRect.CenterPoint().y);

	checkRect = drawRect;
	if (drawInfo.headingUpMode == 1)
	{
		checkRect = GetBoundaryRect(drawRect, (long)angle);
		objRect = GetBoundaryRect(objRect, (long)angle);
	}
std::cout << "Step 11" << std::endl;
	if (!rectBuffer.IntersectRect(&checkRect, &objRect))
	{
		return false;
	}
std::cout << "Step 111" << std::endl;
	inPoint.x -= drawRect.left;
	inPoint.y -= drawRect.top;

	outPoint.x = (long)((800. / 4096.) * inPoint.x);
	outPoint.y = (long)((800. / 4096.) * inPoint.y);
	outPoint.y = drawInfo.devRect.bottom - outPoint.y;

	outPoint.x = outPoint.x + (drawInfo.devCenterPos.x - drawInfo.devRect.CenterPoint().x);
	outPoint.y = outPoint.y + (drawInfo.devCenterPos.y - drawInfo.devRect.CenterPoint().y);

	PointF ttt;
	if (drawInfo.headingUpMode == 1)
	{
		Point temp = Rotate(outPoint, centerPoint, (long)angle);
		ttt.X = temp.x;
		ttt.Y = temp.y;
		g_DrawBuffer[0] = ttt;
	}
	else
	{
		ttt.X = outPoint.x;
		ttt.Y = outPoint.y;
		g_DrawBuffer[0] = ttt;
	}
std::cout << "Step 1111" << std::endl;
	//GetTextExtentPoint(hDC, FieldValue, FieldValue.length(), &textSize);
	textSize.x += 4;
	textSize.y += 4;

	textRect.left = g_DrawBuffer[0].X - (int)(textSize.x / 2) - 1;
	textRect.right = g_DrawBuffer[0].X + (int)(textSize.x / 2) + 1;
	textRect.top = g_DrawBuffer[0].Y - (int)(textSize.y / 2) - 1;
	textRect.bottom = g_DrawBuffer[0].Y + (int)(textSize.y / 2) + 1;

	Color color;

	//oldTextColor = GetTextColor(hDC);
	// SetTextColor(hDC, RGB(150, 79, 223));
	if (drawInfo.dayNightMode == 0)
		color = Color(0, 0, 0);
	else
		color = Color(255, 255, 255);

std::cout << "Step 11111" << std::endl;
	PointF tmp;
	tmp.X = textRect.TopLeft().x;
	tmp.Y = textRect.TopLeft().y;
	const WCHAR* sss = "a";
	// graphics->DrawString(sss /*FieldValue.c_str()*/, -1, &font, tmp, &fillBrush);
std::cout << "Step 111111" << std::endl;
	//SetTextColor(hDC, oldTextColor);
	std::cout << "POINT ==> ( " << tmp.X << ", " << tmp.Y  << ")" << std::endl;  
#if MAP_DISPLAY_DEBUG_MSG
	TRACE("POINT ==> mapType : %d, displayCode : %d\n", mapType, pData->header.code);
	
#endif

	return true;
}

Point CMapDrawEngine::Rotate(Point inPoint, Point centerPoint, long angle)
{
	Point outPoint;

	angle %= 360;

	long cosValue = m_CosValue[angle];
	long sinValue = m_SinValue[angle];

	// ȸ���߽��� center�� ����  O�� ��ġ�ϵ��� ȸ���� �� inPoint�� �Բ� �����̵�
	inPoint.x -= centerPoint.x;
	inPoint.y -= centerPoint.y;

	// ���� O�� ���Ͽ� ȸ���� �� inPoint�� angle ���� ��ŭ ȸ��
	outPoint.x = (inPoint.x * cosValue - inPoint.y * sinValue) / 10000;
	outPoint.y = (inPoint.y * cosValue + inPoint.x * sinValue) / 10000;

	// ���� O�� ������ ȸ�� �߽��� centerPoint�� ��ġ�ϵ��� ȸ���� �� outPoint�� �Բ� �̵�
	outPoint.x += centerPoint.x;
	outPoint.y += centerPoint.y;

	return outPoint;
}

Point CMapDrawEngine::WorldToDevice(const _dPoint _inPoint)
{
	Point	retPoint;

	double	xPos = (long)((_inPoint.x * 28800.) - drawInfo.mapCenterPos.x);
	double	yPos = (long)((_inPoint.y * 28800.) - drawInfo.mapCenterPos.y);

	long	level = _mapFactorInfo.GetTableLevel(0);
	long	xGap = _mapFactorInfo._levelGapTable[1][level];
	long	yGap = _mapFactorInfo._levelGapTable[0][level];

	retPoint.x = (drawInfo.devCenterPos.x + ((long)(xPos * 800. / xGap) << drawInfo.logicalLevel));
	retPoint.y = (drawInfo.devCenterPos.y - ((long)(yPos * 800. / yGap) << drawInfo.logicalLevel));

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

	deltaPoint.x >>= drawInfo.logicalLevel;
	deltaPoint.y >>= drawInfo.logicalLevel;

	deltaMapPoint.x = 4096.;
	deltaMapPoint.y = 4096.;

	deltaMapPoint.x = deltaPoint.x * deltaMapPoint.x / 800.;
	deltaMapPoint.y = deltaPoint.y * deltaMapPoint.y / 800.;

	mapCenterPoint.x -= (long)deltaMapPoint.x;
	mapCenterPoint.y -= (long)deltaMapPoint.y;

	retPoint.x = _mapFactorInfo._basePoint.x + (long)((double)mapCenterPoint.x /
		_mapFactorInfo._levelFactorTable[1][_mapFactorInfo.GetTableLevel(0)]);
	retPoint.y = _mapFactorInfo._basePoint.y + (long)((double)mapCenterPoint.y /
		_mapFactorInfo._levelFactorTable[0][_mapFactorInfo.GetTableLevel(0)]);

	retPoint.x = retPoint.x / 28800.;
	retPoint.y = retPoint.y / 28800.;

	return retPoint;
}

long CMapDrawEngine::GetUTM(_dPoint inPoint, _dPoint& utmPoint, long param)
{
	KW		kw;
	double	tutmx = 0.;
	double	tutmy = 0.;
	double	slam = 0.;
	double	sphi = 0.;
	int		tmp_zone = 0;

		double	tutmxt		= 0.;
		double	tutmyt		= 0.;

	m_Coordinate._dCentralKd = 127;
	m_Coordinate.GetKwbyXY(inPoint.y, inPoint.x, &kw);
	slam = m_Coordinate.GetRadian(kw.kd, kw.kb, kw.kc);	// �浵
	sphi = m_Coordinate.GetRadian(kw.wd, kw.wb, kw.wc);	// ����

	m_Coordinate.GetTawon2utm(0, sphi, slam, &m_BaseZone, &tutmy, &tutmx, 0);

		utmPoint.x = tutmx;
		utmPoint.y = tutmy;

	if (param == 0)
	{
		if (m_BaseZone == 52)
		{
			utmPoint.x = tutmx;
			utmPoint.y = tutmy;
		}
		else
		{
			tmp_zone = 52;
			m_Coordinate.GetTawon2utm(0, sphi, slam, &tmp_zone, &tutmy, &tutmx, 1);
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

long CMapDrawEngine::GetUTM2KW(long izone, _dPoint utmPoint, KW& kw)
{
	double sphi = 0.;
	double slam = 0.;

	m_Coordinate.GetUtm2Tawon(0, &sphi, &slam, izone, utmPoint.y, utmPoint.x);
	m_Coordinate.GetUtm2Tawon(BESSEL, &sphi, &slam, izone, utmPoint.y, utmPoint.x);
	m_Coordinate.GetDMS(sphi, &kw.wd, &kw.wb, &kw.wc);
	m_Coordinate.GetDMS(slam, &kw.kd, &kw.kb, &kw.kc);

	return true;
}


std::string CMapDrawEngine::GetGP2MGRS(_dPoint inPoint)
{
	return m_Coordinate.gp2mgrs(0, inPoint.y, inPoint.x);
}

bool CMapDrawEngine::GetMGRS2KW(std::string mgrs, KW& kw)
{
	return m_Coordinate.mgrs2gp(0, mgrs, kw);
}

std::string CMapDrawEngine::GetUTM2MGRS(int zone, _dPoint utmPoint)
{
	return m_Coordinate.utm2mgrs(0, zone, utmPoint.x, utmPoint.y);
}

bool CMapDrawEngine::GetMGRS2UTM(std::string mgrs, _dPoint& utmPoint)
{
	return m_Coordinate.mgrs2utm(0, mgrs, utmPoint.x, utmPoint.y);
}