#pragma once

#include "type.h"

class Rect {
public:
	int top;
	int bottom;
	int left;
	int right;

public:
	Rect();
	Rect(int l, int t, int r, int b);

	int Width() {
		return right - left;
	}
	int Height() {
		return bottom - top;
	}

	Point TopLeft() {
		return Point(left, top);
	}
	Point CenterPoint() {
		return Point((left + right) / 2, (top + bottom) / 2);
	}

	bool PtInRect(Point p);
	bool IntersectRect(Rect *checkRect, Rect *objRect);

	void SetRect(int l, int t, int r, int b);

};

