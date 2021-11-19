#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "type.h"
#include "pen.h"
#include "brush.h"
#include "font.h"
#include "image.h"

class Graphics
{
	public:
		Graphics(const char *fb_name);
		~Graphics();

		void SetPixel(const Pen *pen, INT x, INT y);
		void SetPixel(const Pen *pen, const PointF &pt);

		void DrawLine(const Pen *pen, INT x1, INT y1, INT x2, INT y2);
		void DrawLine(const Pen *pen, const PointF &pt1, const PointF &pt2);

		void DrawLines(const Pen *pen, const PointF *points, INT count);

		void DrawPolygon(const Pen *pen, const PointF *points, INT count);
		void FillPolygon(const Brush *brush, const PointF *points, INT count);

		void DrawRectangle(const Pen *pen, INT x, INT y, INT width, INT height);
		void DrawRectangle(const Pen *pen, const RectF &rect);
		void FillRectangle(const Brush *brush, INT x, INT y, INT width, INT height);
		void FillRectangle(const Brush *brush, const RectF &rect);

		void DrawEllipse(const Pen *pen, INT x, INT y, INT width, INT height);
		void DrawEllipse(const Pen *pen, const RectF &rect);
		void FillEllipse(const Brush *brush, INT x, INT y, INT width, INT height);
		void FillEllipse(const Brush *brush, const RectF &rect);

		void DrawString(const WCHAR *string, INT length, const Font *font, const PointF& origin, const Brush *brush);
		void DrawImage(Image *image, const PointF &point);
};

#endif
