#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <cairo/cairo.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "type.h"
#include "pen.h"
#include "font.h"
#include "brush.h"

void linuxfb_surface_destroy(void *device);
cairo_surface_t *linuxfb_surface_create(const char *fb_name);

class Graphics
{
	public:
		Graphics(const char *fb_name);
		~Graphics();
		void DrawLine(const Pen *pen, INT x1, INT y1, INT x2, INT y2);
		void DrawRectangle(const Pen *pen, INT x, INT y, INT width, INT height);
		void FillRectangle(const Brush *brush, INT x, INT y, INT width, INT height);
		void DrawString(const std::string *string, INT length, const Font *font, const PointF& origin, const Brush *brush);
	private:
		cairo_surface_t *surface;
		cairo_t *cr;
};

#endif
