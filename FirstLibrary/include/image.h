#ifndef __IMAGE_PRIV_H__
#define __IMAGE_PRIV_H__

#include "type.h"

using namespace std;

class Image
{
	public:
		Image(const WCHAR *filename);
		void ImageClose();
};

#endif
