#pragma once

#include <string>

class Image
{
public:
	Image();
	Image(std::string filename);
	void ImageClose();
	int reserve_pub[3];
private:
	int reserve_pri[4];
};