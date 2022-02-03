#include "./include/type.h"

namespace GREEN_MAP_CONST
{
	const int		MAP_CODE_LENGTH = 8;
	const int		BASE_PARCEL_GAP_X = 7200;
	const int		BASE_PARCEL_GAP_Y = 4800;
	const int		MAX_TEXT_LENGTH = 64;
	const double		PI_VALUE = 3.141592653589793238462643383279502884197169399375105820974944592308;

	const Color BLACK_COLOR	Color(255, 0, 0, 0);
	const Color RED_COLOR	Color(255, 255, 0, 0);
	const Color GREEN_COLOR	Color(255, 0, 255, 0);
	const Color BLUE_COLOR	Color(255, 0, 0, 255);
	const Color PURPLE_COLOR	Color(255, 255, 0, 255);
	const Color WHITE_COLOR	Color(255, 255, 255, 255);
	const Color MISSION_COLOR	Color(255, 247, 104, 12);

	// 20120115 User Layer Line Color
	// const Color ORANGE_COLOR	Color(255, 219, 77, 36);
	const Color ORANGE_COLOR	Color(255, 250, 192, 144);

	const Color	GEN_TEXT_COLOR[2] =
	{
		Color(255,   0,   0,  0),
		Color(255,  29, 229, 29)
	};

	const Color	MAP_GEN_TEXT_COLOR[2] =
	{
		Color(255,   0,   0,  0),
		Color(255,  255, 255, 255)
	};

	const Color	REV_TEXT_COLOR[2] =
	{
		Color(255, 255, 255, 255),
		Color(255,   0,   0,   0)
	};

	namespace MAP_PARCEL_STATE
	{
		const int		NORMAL_STATE = 0x00;
		const int		BOUNDARY_LEFT = 0x01;
		const int		BOUNDARY_RIGHT = 0x02;
		const int		BOUNDARY_TOP = 0x10;
		const int		BOUNDARY_BOTTOM = 0x20;
		const int		BOUNDARY_ALL = 0x33;
	}

	namespace MAP_CODE_INDEX
	{
		const int		MINOR_CODE = 0;
		const int		MAJOR_CODE = 1;
		const int		INDEX_COUNT = 2;
	}

	namespace MAP_COORD_TYPE
	{
		const int		WGS_84_TYPE = 0;
		const int		BESSEL_TYPE = 1;
		const int		UTM_TYPE = 2;
	}

	namespace MAP_POSITION_INDEX
	{
		const int		LATITUDE = 0;
		const int		LONGITUDE = 1;
		const int		INDEX_COUNT = 2;
	}

	namespace CODEWCHARECK_FIELD
	{
		const int		FIELD_NAME = 0;
		const int		FIELD_VALUE = 1;
		const int		INDEX_COUNT = 2;
		const int		FIELD_MAX_LENGTH = 16;
	}

	namespace MAP_COORD_TYPE
	{
		const int		WGS_84 = 0;
		const int		BESSEL = 1;
	}

	namespace MAP_MODE_HEADING
	{
		const long		MAP_MODE_NORTH_UP = 0;				// 노스업
		const long		MAP_MODE_HEADING_UP = 1;				// 헤딩업
		const long		COUNT = 2;
	}

	namespace MAP_MODE_PANNING
	{
		const long		MODE_NORMAL = 0;
		const long		MODE_PANNING = 1;
	}

	namespace MAP_MODE_DAYNIGHT
	{
		const long		MAP_MODE_DAY = 0;				// 주간 모드
		const long		MAP_MODE_NIGHT = 1;				// 야간 모드

		const long		COUNT = 2;
	}

}

namespace DESIGN_CONST
{
	// Default Enum Type Define
	namespace IMAGE_TYPE
	{
		const unsigned char BMP = 0;
		const unsigned char JPEG = 1;
		const unsigned char PNG = 2;
	}

	namespace DRAW_TYPE
	{
		const unsigned char POINT = 0;
		const unsigned char POLYLINE = 1;
		const unsigned char POLYGON = 2;

		namespace POINT_TYPE
		{
			const unsigned char NONE = 0x00;
			const unsigned char TEXT = 0x01;
			const unsigned char SYMBOL = 0x02;

			namespace TEXT_POSITION
			{
				const unsigned char LT = 0;
				const unsigned char T = 1;
				const unsigned char RT = 2;
				const unsigned char L = 3;
				const unsigned char C = 4;
				const unsigned char R = 5;
				const unsigned char LB = 6;
				const unsigned char B = 7;
				const unsigned char RB = 8;
			}

			namespace FONT_EFFECT
			{
				const unsigned char NORMAL = 0x00;
				const unsigned char BOLD = 0x01;
				const unsigned char ITALIC = 0x02;
				const unsigned char UNDERLINE = 0x04;
			}
		}

		namespace LINE_TYPE
		{
			const unsigned char SOLID = 0;	// PS_SOLID			Creates a solid pen.
			const unsigned char DASH = 1;	// PS_DASH			Creates a dashed pen. Valid only when the pen width is 1 or less, in device units.
			const unsigned char DOT = 2;	// PS_DOT			Creates a dotted pen. Valid only when the pen width is 1 or less, in device units.
			const unsigned char DASHDOT = 3;	// PS_DASHDOT		Creates a pen with alternating dashes and dots. Valid only when the pen width is 1 or less, in device units.
			const unsigned char DASHDOTDOT = 4;	// PS_DASHDOTDOT	Creates a pen with alternating dashes and double dots. Valid only when the pen width is 1 or less, in device units.
			const unsigned char NULLPEN = 5;	// PS_NULL			Creates a null pen.
		}

		namespace BRUSH_TYPE
		{
			const unsigned char NULLBRUSH = 0x00;
			const unsigned char SOLID_MASK = 0x10;
			const unsigned char HATCH_MASK = 0x20;
			const unsigned char PATTERN_MASK = 0x40;
			const unsigned char SOLID = 0x11;
			const unsigned char HATCH_HORIZONTAL = 0x21;		// HS_HORIZONTAL   Horizontal hatch
			const unsigned char HATCH_VERTICAL = 0x22;		// HS_VERTICAL   Vertical hatch
			const unsigned char HATCH_FDIAGONAL = 0x23;		// HS_FDIAGONAL   Upward hatch (left to right) at 45 degrees
			const unsigned char HATCH_BDIAGONAL = 0x24;		// HS_BDIAGONAL   Downward hatch (left to right) at 45 degrees
			const unsigned char HATCH_CROSS = 0x25;		// HS_CROSS   Horizontal and vertical crosshatch
			const unsigned char HATCH_DIAGCROSS = 0x26;		// HS_DIAGCROSS   Crosshatch at 45 degrees				
			const unsigned char PATTERN_BMP = 0x41;
			const unsigned char PATTERN_JPEG = 0x42;
			const unsigned char PATTERN_PNG = 0x43;
		}
	}
}