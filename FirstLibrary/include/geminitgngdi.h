#ifndef __GEMINITGNGDI_H__
#define __GEMINITGNGDI_H__

#include "graphics.h"
#include "brush.h"
#include "font.h"
#include "image.h"
#include "pen.h"
#include "type.h"

extern "C" {
Pen CreatePen(INT _style, REAL _width, const Color &_color);
}

#endif

