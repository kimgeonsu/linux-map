#ifndef __IMAGE_PRIV_H__
#define __IMAGE_PRIV_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <iostream>
#include <fstream>
#include <cmath>
extern "C" {
#include "type.h"
#include "gx.h"
}

#define IMAGE_TYPE_BMP	1
#define IMAGE_TYPE_JPG	2
#define IMAGE_TYPE_PNG	3

using namespace std;

class Image
{
	public:
		Image();
		Image(const WCHAR *filename);
		void ImageClose();
		int reserve_pub[3];
	private:
		int reserve_pri[4];
};

#endif
