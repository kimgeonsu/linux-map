#pragma once
// AppLib.h: interface for the CAppLib class.
//
//////////////////////////////////////////////////////////////////////
#include <string>
#include <math.h>
#include "MyType.h"

template <typename dataSize>
inline dataSize GlConvertByteOrder(dataSize data)
{
	dataSize	RetValue = 0;
	switch (sizeof(dataSize))
	{
	case 2:
		// 2byte Data Process
		RetValue = ((data & 0xff00) >> 8) | ((data & 0x00ff) << 8);
		break;
	case 4:
		// 4byte Data Process
		RetValue = ((data & 0xff000000) >> 24) | ((data & 0x00ff0000) >> 8) |
			((data & 0x0000ff00) << 8) | ((data & 0x000000ff) << 24);
		break;
	case 8:
		// Not Support
		break;
	}
	return RetValue;
}

template <typename dataType>
inline void GlReleaseMem(dataType** pMem)
{
	if (*pMem != NULL)
	{
		delete* pMem;//Type Mismatch
		*pMem = NULL;
	}
}

template <typename dataTypeArry>
inline void GlReleaseArray(dataTypeArry** pMem)
{
	if (*pMem != NULL)
	{
		delete[] * pMem;
		*pMem = NULL;
	}
}

template <typename dataTypeHOBJ>
inline void GlReleaseHOBJ(dataTypeHOBJ* hObj)
{
	if (*hObj != NULL)
	{
		DeleteObject(*hObj);
		*hObj = NULL;
	}
}

namespace APPLIB_CONST
{
	const long		FactorTable[10][3] =
	{
		{ 0, 0, 0},	// N
		{ 8, 0, 0},	// P
		{ 7, 0, 2},	// Q
		{ 6, 2, 2},	// R
		{ 5, 2, 4},	// S
		{ 4, 4, 5},	// T
		{ 3, 5, 6},	// U
		{ 2, 6, 7},	// V
		{ 0, 7, 7},	// W
		{ 9, 7, 8},	// X
	};

	const short MslTable[36][19] =
	{
		{13, 33, 51, 47, 47, 52, 36, 31, 22, 18, 12, 17, 22, 18, 25, 16, 16, -4, -30},
		{13, 34, 43, 41, 48, 48, 28, 26, 23, 12, 13, 23, 27, 26, 26, 19, 16, -1, -30},
		{13, 28, 29, 21, 42, 35, 29, 15,  2,-13, -2, 21, 34, 31, 34, 25, 17,  1, -30},
		{13, 23, 20, 18, 28, 40, 17,  6, -3, -9,-14,  8, 29, 33, 39, 30, 21,  4, -30},
		{13, 17, 12, 14, 12, 33, 12,  1, -7,-28,-25, -9, 14, 39, 45, 35, 20,  4, -30},
		{13, 13,  5,  7,-10, -9,-20,-29,-36,-49,-32,-10, 15, 41, 45, 35, 26,  6, -30},
		{13,  9, -2, -3,-19,-28,-15,-44,-59,-62,-38,-11, 15, 30, 38, 33, 26,  5, -30},
		{13,  4,-10,-22,-33,-39,-40,-61,-90,-89,-60,-20,  7, 24, 39, 30, 22,  4, -30},
		{13,  4,-14,-29,-43,-48,-33,-67,-95,-102,-75,-40,-9, 13, 28, 27, 16,  2, -30},
		{13,  1,-12,-32,-42,-59,-34,-59,-63,-63,-63,-47,-25, -2, 13, 10, 10, -6, -30},
		{13, -2,-10,-32,-43,-50,-34,-36,-24, -9,-26,-45,-37,-20, -1, -2, -1,-15, -30},
		{13, -2,-14,-26,-29,-28,-28,-11, 12, 33,  0,-25,-39,-32,-15,-14,-16,-24, -30},
		{13,  0,-12,-15, -2,  3,  7, 21, 53, 58, 35,  5,-23,-33,-22,-23,-29,-33, -30},
		{13,  2, -6, -2, 17, 23, 29, 39, 60, 73, 52, 23,-14,-27,-22,-30,-36,-40, -30},
		{13,  3, -2, 13, 23, 37, 43, 49, 58, 74, 68, 45, 15,-14,-18,-33,-46,-48, -30},
		{13,  2,  3, 17, 22, 18, 20, 39, 46, 63, 76, 58, 33, -2,-15,-29,-55,-50, -30},
		{13,  1,  6, 19,  6, -1,  4, 22, 36, 50, 64, 57, 34,  5,-14,-35,-54,-53, -30},
		{13,  1,  4,  6,  2,-11, -6, 10, 26, 32, 52, 63, 45, 20,-10,-43,-59,-52, -30},
		{13,  3,  2,  2, -8,-12, -7,  5, 13, 22, 36, 51, 46, 21,-15,-45,-61,-53, -30},
		{13,  1,  2,  9,  8,-10, -5, 10, 12, 16, 22, 27, 22,  6,-18,-43,-60,-54, -30},
		{13, -2,  1, 17,  8,-13, -8,  7, 11, 17, 11, 10,  5,  1,-18,-37,-61,-55, -30},
		{13, -3, -1, 10,  1,-20,-15, -7,  2, 13,  6,  0, -2, -7,-16,-32,-55,-52, -30},
		{13, -3, -3, 13,-11,-31,-28,-23,-11,  1, -1, -9, -8,-12,-17,-30,-49,-48, -30},
		{13, -3, -7,  1,-19,-34,-40,-39,-28,-12, -8,-11,-13,-12,-15,-26,-44,-42, -30},
		{13, -1,-14,-14,-16,-21,-42,-47,-38,-23,-10, -5,-10,-12,-10,-23,-38,-38, -30},
		{13,  3,-24,-30,-18,-16,-29,-34,-29,-20, -8, -2, -7,-10,-10,-22,-31,-38, -30},
		{13,  1,-27,-39,-22,-26,-22, -9,-10,-14,-11, -3, -4, -7, -8,-16,-25,-29, -30},
		{13,  5,-25,-46,-35,-34,-26,-10,  3, -3, -9, -1,  1, -1, -2,-10,-16,-26, -30},
		{13,  9,-19,-42,-40,-33,-32,-20,  1, 14,  1,  9,  9,  8,  6, -2, -6,-26, -30},
		{13, 11,  3,-21,-26,-35,-51,-45,-11, 10, 32, 35, 32, 23, 14, 10,  1,-24, -30},
		{13, 19, 24,  6,-12,-26,-40,-48,-41,-15,  4, 20, 16, 15, 13, 20,  4,-23, -30},
		{13, 27, 37, 29, 24,  2,-17,-32,-42,-27,-18, -5,  4, -2,  3, 20,  5,-21, -30},
		{13, 31, 47, 49, 45, 33, 17, -9,-16,-18,-13, -6, -8, -6,  3, 21,  4,-19, -30},
		{13, 34, 60, 65, 63, 59, 31, 17,  3,  3, -9, -5,  4,  6, 10, 24,  2,-16, -30},
		{13, 33, 61, 60, 62, 52, 34, 25, 17, 12,  4,  0, 12, 21, 20, 22,  6,-12, -30},
		{13, 34, 58, 57, 59, 51, 44, 31, 33, 20, 14, 13, 15, 24, 27, 17, 12, -8, -30}
	};

	const unsigned long CRC_TABLE[256] =
	{
		0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005,
			0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61, 0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd,
			0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
			0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3, 0x709f7b7a, 0x745e66cd,
			0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039, 0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5,
			0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
			0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95,
			0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1, 0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d,
			0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
			0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4, 0x0808d07d, 0x0cc9cdca,
			0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde, 0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02,
			0x5e9f46bf, 0x5a5e5b08, 0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
			0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692,
			0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6, 0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a,
			0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
			0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a,
			0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637, 0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb,
			0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
			0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5, 0x3f9b762c, 0x3b5a6b9b,
			0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff, 0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623,
			0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
			0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3,
			0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7, 0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b,
			0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
			0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c,
			0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8, 0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24,
			0x119b4be9, 0x155a565e, 0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
			0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654,
			0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0, 0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c,
			0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
			0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c,
			0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668, 0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
	};

	const char* const MGRSText = "ABCDEFGHJKLMNPQRSTUVWXYZABCDEFG";
	const char* const MGRSTextY = "ABCDEFGHJKLMNPQRSTUVABCDEFG";

	const double Coord_dCentralKd = 127.0;
	const double Coord_dScalingWd = 38.0;
	const double Coord_dFactor = 0.9996;
	const double Coord_dFalseNorth = 500000.0;
	const double Coord_dFalseEast = 200000.0;
}

#define POLYNOMIAL	0x04c11db7L

class CAppLib
{
protected:

public:
	double GetDistance(_dPoint a, _dPoint b);
	static void Coord_GetDMSbyDegree(_dPoint latlon, _LatLonDMS& latlonDMS);
	void Coord_GetDegreebyDMS(_LatLonDMS latlonDMS, _dPoint& latlon);
	static void Coord_GetDMS(double radian, short& dd, short& mm, double& ss);
	static double Coord_GetRadian(short dd, short mm, double ss);
	static bool	Coord_MGRS2UTM(std::string mgrs, _dPoint& utmPoint);
	static std::string Coord_UTM2MGRS(int tawon, int zone, _dPoint utmPoint);
	static void	Coord_Tawon2UTM(int tawon, double sphi, double slam, int* izone, double* y, double* x, int ifixz);
	static void	Coord_UTM2Tawon(int tawon, double* sphi, double* slam, int izone, double y, double x);


public:
	CAppLib();
	virtual ~CAppLib();

};
