#pragma once

#include "type.h"
#include "tmp_pen.h"
#include "tmp_brush.h"
#include "tmp_font.h"
#include "tmp_image.h"
#include <string>

using namespace std;

class Graphics
{
public:
	Graphics(const char* fb_name) {}
	~Graphics() {}

	void SetPixel(const Pen* pen, int x, int y) {
		cout << "-----I'm SetPixel-----\n";
		cout << "pen : " << pen << endl;
		cout << "x : " << x << endl;
		cout << "y : " << y << endl;
	}
	void SetPixel(const Pen* pen, const Point& pt) {
		cout << "-----I'm SetPixel-----\n";
		cout << "pen : " << pen << endl;
		cout << "pt : " << pt.x  << " , " << pt.y << endl;
	}

	void DrawLine(const Pen* pen, int x1, int y1, int x2, int y2) {
		cout << "-----I'm DrawLine-----\n";
		cout << "pen : " << pen << endl;
		cout << "x1 : " << x1 << endl;
		cout << "y1 : " << y1 << endl;
		cout << "x2 : " << x2 << endl;
		cout << "y2 : " << y2 << endl;
	}
	void DrawLine(const Pen* pen, const Point& pt1, const Point& pt2) {
		cout << "-----I'm DrawLine-----\n";
		cout << "pen : " << pen << endl;
		cout << "pt1 : " << pt1.x << " , " << pt1.y << endl;
		cout << "pt2 : " << pt2.x << " , " << pt2.y << endl;
	}

	void DrawLines(const Pen* pen, const Point* points, int count) {
		cout << "-----I'm DrawLine-----\n";
		cout << "pen : " << pen << endl;
		cout << "ponints : " << points->x << " , " << points->y << endl;
		cout << "count : " << count << endl;
	}

	void DrawPolygon(const Pen* pen, const Point* points, int count) {
		cout << "-----I'm DrawPolygon-----\n";
		cout << "pen : " << pen << endl;
		cout << "ponints : " << points->x << " , " << points->y << endl;
		cout << "count : " << count << endl;
	}
	void FillPolygon(const Brush* brush, const Point* points, int count) {
		cout << "-----I'm FillPolygon-----\n";
		cout << "brush : " << brush << endl;
		cout << "ponints : " << points->x << " , " << points->y << endl;
		cout << "count : " << count << endl;
	}

	void DrawRectangle(const Pen* pen, int x, int y, int width, int height) {
		cout << "-----I'm DrawRectangle-----\n";
		cout << "pen : " << pen << endl;
		cout << "x : " << x << endl;
		cout << "y : " << y << endl;
		cout << "width : " << width << endl;
		cout << "height : " << height << endl;
	}
	void DrawRectangle(const Pen* pen, const RectF& RectF) {
		cout << "-----I'm DrawRectangle-----\n";
		cout << "pen : " << pen << endl;
		cout << "RectF.top : " << RectF.top << endl;
		cout << "RectF.bottom : " << RectF.bottom << endl;
		cout << "RectF.left : " << RectF.left << endl;
		cout << "RectF.right : " << RectF.right << endl;
	}
	void FillRectangle(const Brush* brush, int x, int y, int width, int height) {
		cout << "-----I'm FillRectangle-----\n";
		cout << "brush : " << brush << endl;
		cout << "x : " << x << endl;
		cout << "y : " << y << endl;
		cout << "width : " << width << endl;
		cout << "height : " << height << endl;
	}
	void FillRectangle(const Brush* brush, const RectF& RectF) {
		cout << "-----I'm FillRectangle-----\n";
		cout << "brush : " << brush << endl;
		cout << "RectF.top : " << RectF.top << endl;
		cout << "RectF.bottom : " << RectF.bottom << endl;
		cout << "RectF.left : " << RectF.left << endl;
		cout << "RectF.right : " << RectF.right << endl;
	}

	void DrawEllipse(const Pen* pen, int x, int y, int width, int height) {
		cout << "-----I'm Drawellipse-----\n";
		cout << "pen : " << pen << endl;
		cout << "x : " << x << endl;
		cout << "y : " << y << endl;
		cout << "width : " << width << endl;
		cout << "height : " << height << endl;
	}
	void DrawEllipse(const Pen* pen, const RectF& RectF) {
		cout << "-----I'm DrawEllipse-----\n";
		cout << "pen : " << pen << endl;
		cout << "RectF.top : " << RectF.top << endl;
		cout << "RectF.bottom : " << RectF.bottom << endl;
		cout << "RectF.left : " << RectF.left << endl;
		cout << "RectF.right : " << RectF.right << endl;
	}
	void FillEllipse(const Brush* brush, int x, int y, int width, int height) {
		cout << "-----I'm FillEllipse-----\n";
		cout << "brush : " << brush << endl;
		cout << "x : " << x << endl;
		cout << "y : " << y << endl;
		cout << "width : " << width << endl;
		cout << "height : " << height << endl;
	}
	void FillEllipse(const Brush* brush, const RectF& RectF) {
		cout << "-----I'm Fillellipse-----\n";
		cout << "brush : " << brush << endl;
		cout << "RectF.top : " << RectF.top << endl;
		cout << "RectF.bottom : " << RectF.bottom << endl;
		cout << "RectF.left : " << RectF.left << endl;
		cout << "RectF.right : " << RectF.right << endl;
	}

	void DrawString(std::string str, int length, const Font* font, const Point& origin, const Brush* brush) {
		cout << "-----I'm DrawString-----\n";
		cout << "str : " << str << endl;
		cout << "length : " << length << endl;
		cout << "font : " << font << endl;
		cout << "origin : " << origin.x << " , " << origin.y << endl;
		cout << "brush : " << brush << endl;
	}
	void DrawImage(Image* image, const Point& point) {
		cout << "-----I'm DrawImage-----\n";
		cout << "image : " << image << endl;
		cout << "point : " << point.x << " , " << point.y << endl;
	}
};