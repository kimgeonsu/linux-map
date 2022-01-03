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
#include <sstream>
#include <cmath>
#include <vector>
#include <unistd.h>

extern "C" {
#include "./include/type.h"
#include "./include/pen.h"
#include "./include/brush.h"
#include "./include/graphics.h"
}

#include "MapDrawEngine.h"

using namespace std;

Graphics 	*graphics;
Color 		 color(0, 0, 0);
Pen 		 pen(color, 1.0);
Brush 		 brush(color);

int main()
{
    // std::string dataFilePath = "../Output";
    // CMapDrawEngine *engine = new CMapDrawEngine;
    // engine->Init();
    // engine->SetMapDataPath(dataFilePath);
	// engine->SetDeviceRect(0, 0, 480, 800);
	// engine->SetDeviceCenterPos(240, 400);

	// engine->SetZoomLevel(0);
	// engine->SetMapPos(128.0, 36.0);

	// int currentAngle = 0;
	// int currentMapMode = 1;
	// engine->SetMapAngle(currentAngle);
	// engine->SetMapHeadingUpMode(currentMapMode);
    // engine->SetMapDayNightMode(0);

    // _dPoint dp;
    // dp.x = 128.5; 
    // dp.y = 36.5;
    // Point ip = Point(10,10);
    // engine->WorldToDevice(dp);
    // engine->DeviceToWorldMove(ip, ip);
    // engine->DrawMap();

    // string cmd;
	// vector<string> commands;
	// double data1, data2;
    // while (1) {
    //     cout << "명령어를 입력하세용 : ";
	// 	getline(cin, cmd);
	// 	istringstream foo(cmd);
	// 	string token;

	// 	while(getline(foo, token, ' ')) {
	// 		commands.push_back(token);
	// 	}

	// 	cout << cmd << endl;

    //     if (commands[0] == "move") {
	// 		engine->MoveMap(stol(commands[1]), stol(commands[2]));
	// 		engine->DrawMap();
    //     }
    //     if (commands[0] == "rotate") {
	// 		engine->SetMapAngle(stol(commands[1]));
	// 		engine->DrawMap();
	// 	}
	// 	if (commands[0] == "zoom") {
	// 		engine->SetZoomLevel(stol(commands[1]));
	// 		engine->DrawMap();
	// 	}
	// 	if (commands[0] == "dark") {
	// 		engine->SetMapDayNightMode(0);
	// 		engine->DrawMap();
	// 	}
	// 	if (commands[0] == "light") {
	// 		engine->SetMapDayNightMode(1);
	// 		engine->DrawMap();
	// 	}
    //     if (commands[0] == "exit") {
	// 		std::cout << "바이 바이 ~~~~\n";
    //         return 0;
    //     }
	// 	commands.clear();
    // }

	graphics = new Graphics("/dev/fb0");

	//Screen clear.
	Brush clear(Color(255, 255, 255));
	graphics->FillRectangle(&clear, RectF(0, 0, 800, 480));


	brush.SetColor(Color(255,127,39));

	PointF fox_pts[] = {
		PointF(28 , -1335),
PointF(39 , -1327),
PointF(47 , -1321),
PointF(49 , -1312),
PointF(45 , -1301),
PointF(51 , -1288),
PointF(54 , -1279),
PointF(45 , -1272),
PointF(40 , -1261),
PointF(28 , -1260),
PointF(22 , -1251),
PointF(25 , -1239),
PointF(32 , -1230),
PointF(42 , -1230),
PointF(42 , -1220),
PointF(44 , -1210),
PointF(49 , -1201),
PointF(51 , -1192),
PointF(56 , -1183),
PointF(65 , -1180),
PointF(64 , -1171),
PointF(65 , -1162),
PointF(66 , -1152),
PointF(72 , -1142),
PointF(80 , -1138),
PointF(92 , -1131),
PointF(100 , -1129),
PointF(108 , -1131),
PointF(114 , -1138),
PointF(121 , -1147),
PointF(129 , -1150),
PointF(136 , -1148),
PointF(140 , -1132),
PointF(140 , -1122),
PointF(139 , -1110),
PointF(131 , -1099),
PointF(121 , -1088),
PointF(118 , -1080),
PointF(119 , -1067),
PointF(121 , -1059),
PointF(122 , -1049),
PointF(120 , -1037),
PointF(110 , -1031),
PointF(100 , -1023),
PointF(91 , -1019),
PointF(86 , -1010),
PointF(85 , -999),
PointF(80 , -988),
PointF(64 , -984),
PointF(53 , -972),
PointF(43 , -969),
PointF(40 , -960),
PointF(41 , -949),
PointF(37 , -939),
PointF(29 , -930),
PointF(25 , -921),
PointF(24 , -910),
PointF(22 , -899),
PointF(18 , -891),
PointF(9 , -880),
PointF(3 , -868),
PointF(0 , -860),
// PointF(-10 , -856),
// PointF(-18 , -846),
// PointF(-28 , -842),
// PointF(-41 , -832),
// PointF(-48 , -823),
// PointF(-49 , -813),
// PointF(-59 , -809),
// PointF(-68 , -804),
// PointF(-78 , -796),
// PointF(-89 , -804),
// PointF(-97 , -810),
// PointF(-109 , -810),
// PointF(-122 , -813),
// PointF(-132 , -821),
// PointF(-141 , -834),
// PointF(-147 , -842),
// PointF(-156 , -849),
// PointF(-163 , -863),
// PointF(-172 , -864),
// PointF(-184 , -870),
// PointF(-193 , -866),
// PointF(-206 , -873),
// PointF(-215 , -879),
// PointF(-226 , -887),
// PointF(-236 , -897),
// PointF(-235 , -905),
// PointF(-242 , -919),
// PointF(-245 , -928),
// PointF(-242 , -938),
// PointF(-238 , -949),
// PointF(-238 , -958),
// PointF(-241 , -966),
// PointF(-251 , -970),
// PointF(-257 , -979),
// PointF(-268 , -988),
// PointF(-277 , -995),
// PointF(-270 , -1003),
// PointF(-267 , -1013),
// PointF(-259 , -1015),
// PointF(-251 , -1018),
// PointF(-251 , -1026),
// PointF(-243 , -1031),
// PointF(-235 , -1027),
// PointF(-227 , -1027),
// PointF(-224 , -1035),
// PointF(-233 , -1038),
// PointF(-229 , -1046),
// PointF(-221 , -1054),
// PointF(-213 , -1060),
// PointF(-205 , -1067),
// PointF(-200 , -1058),
// PointF(-189 , -1064),
// PointF(-181 , -1068),
// PointF(-174 , -1062),
// PointF(-161 , -1067),
// PointF(-162 , -1077),
// PointF(-153 , -1077),
// PointF(-151 , -1085),
// PointF(-147 , -1094),
// PointF(-135 , -1111),
// PointF(-138 , -1119),
// PointF(-130 , -1125),
// PointF(-123 , -1133),
// PointF(-114 , -1142),
// PointF(-107 , -1145),
// PointF(-100 , -1156),
// PointF(-99 , -1163),
// PointF(-92 , -1171),
// PointF(-89 , -1182),
// PointF(-82 , -1190),
// PointF(-75 , -1204),
// PointF(-66 , -1209),
// PointF(-58 , -1203),
// PointF(-54 , -1211),
// PointF(-60 , -1219),
// PointF(-60 , -1227),
// PointF(-57 , -1235),
// PointF(-53 , -1243),
// PointF(-50 , -1256),
// PointF(-44 , -1264),
// PointF(-45 , -1272),
// PointF(-49 , -1283),
// PointF(-39 , -1290),
// PointF(-40 , -1298),
// PointF(-32 , -1295),
// PointF(-24 , -1302),
// PointF(-16 , -1310),
// PointF(-25 , -1318),
// PointF(-17 , -1323),
// PointF(-9 , -1316),
// PointF(-6 , -1307),
// PointF(-2 , -1315),
// PointF(0 , -1323),
// PointF(7 , -1316),
// PointF(9 , -1324),
// PointF(12 , -1331),
// PointF(22 , -1340),
// PointF(28 , -1335),
	};

	int cntPoint = sizeof fox_pts/sizeof fox_pts[0];
	std::cout << cntPoint << std::endl;

	graphics->FillPolygon(&brush, fox_pts, cntPoint);
	graphics->DrawPolygon(&pen, fox_pts, cntPoint);
	//

	graphics->~Graphics();


	return 0;
}
