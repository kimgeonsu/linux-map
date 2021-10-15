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

typedef struct _linuxfb_device {
	int fb_fd;
	unsigned char *fb_data;
	long fb_screensize;
	struct fb_var_screeninfo fb_vinfo;
	struct fb_fix_screeninfo fb_finfo;
} linuxfb_device_t;

typedef struct Color {
	INT r;
	INT g;
	INT b;

	Color(): r(0), g(0), b(0) {}
	Color(INT R, INT G, INT B): r(R), g(G), b(B) {}
} Color;

#endif
