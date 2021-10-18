#ifndef __TYPE_H__
#define __TYPE_H__

typedef int INT;

typedef float REAL;

typedef char WCHAR;

typedef struct PointF {
	REAL X;
	REAL Y;

	PointF(): X(0.0f), Y(0.0f) {}
	PointF(REAL x, REAL y): X(x), Y(y) {}
} PointF;

typedef struct RectF {
	REAL X;
	REAL Y;
	REAL Width;
	REAL Height;

	RectF(): X(0.0f), Y(0.0f), Width(0.0f), Height(0.0f) {}
	RectF(REAL x, REAL y, REAL width, REAL height):
		X(x), Y(y), Width(width), Height(height) {}
} RectF;

typedef struct Color {
	INT r;
	INT g;
	INT b;

	Color(): r(0), g(0), b(0) {}
	Color(INT R, INT G, INT B): r(R), g(G), b(B) {}
} Color;

#endif
