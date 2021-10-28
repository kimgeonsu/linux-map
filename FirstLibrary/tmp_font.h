#pragma once

#include <string>

class Font
{
	std::string font;
	double fontSize;
public:
	Font() : font(""), fontSize(0) {}
	Font(std::string family, double size) {
		font = family;
		fontSize = size;
	}
};