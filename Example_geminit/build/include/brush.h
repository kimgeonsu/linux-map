#ifndef __BRUSH_H__
#define __BRUSH_H__

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

class Brush
{
	public:
		Brush();
};

#endif
