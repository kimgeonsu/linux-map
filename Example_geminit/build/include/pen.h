#ifndef __PEN_H__
#define __PEN_H__

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

class Pen
{
	public:
		Pen();
		Pen(const Color &color, REAL width = 1.0f);
		Color color;
		REAL width;
};

#endif
