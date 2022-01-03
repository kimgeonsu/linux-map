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

	// PointF fox_pts[] = {
	// 	PointF(891 , -1799),
	// PointF(891 , -1785),
	// PointF(886 , -1775),
	// PointF(877 , -1761),
	// PointF(879 , -1751),
	// PointF(880 , -1742),
	// PointF(873 , -1731),
	// PointF(867 , -1720),
	// PointF(860 , -1709),
	// PointF(859 , -1696),
	// PointF(865 , -1688),
	// PointF(865 , -1678),
	// PointF(852 , -1674),
	// PointF(843 , -1675),
	// PointF(845 , -1661),
	// PointF(833 , -1656),
	// PointF(822 , -1659),
	// PointF(810 , -1656),
	// PointF(800 , -1660),
	// PointF(794 , -1651),
	// PointF(784 , -1650),
	// PointF(772 , -1651),
	// PointF(762 , -1645),
	// PointF(752 , -1641),
	// PointF(740 , -1635),
	// PointF(726 , -1623),
	// PointF(720 , -1613),
	// PointF(729 , -1608),
	// PointF(736 , -1604),
	// PointF(745 , -1608),
	// PointF(754 , -1600),
	// PointF(762 , -1588),
	// PointF(765 , -1577),
	// PointF(761 , -1567),
	// PointF(752 , -1565),
	// PointF(754 , -1552),
	// PointF(757 , -1542),
	// PointF(761 , -1532),
	// PointF(752 , -1531),
	// PointF(752 , -1538),
	// PointF(750 , -1546),
	// PointF(749 , -1554),
	// PointF(744 , -1562),
	// PointF(741 , -1574),
	// PointF(743 , -1582),
	// PointF(734 , -1585),
	// PointF(731 , -1576),
	// PointF(735 , -1567),
	// PointF(724 , -1566),
	// PointF(723 , -1574),
	// PointF(725 , -1582),
	// PointF(716 , -1578),
	// PointF(711 , -1588),
	// PointF(702 , -1595),
	// PointF(698 , -1606),
	// PointF(690 , -1611),
	// PointF(686 , -1620),
	// PointF(688 , -1627),
	// PointF(685 , -1635),
	// PointF(686 , -1644),
	// PointF(690 , -1654),
	// PointF(693 , -1663),
	// PointF(691 , -1670),
	// PointF(682 , -1670),
	// PointF(674 , -1673),
	// PointF(661 , -1673),
	// PointF(662 , -1685),
	// PointF(668 , -1693),
	// PointF(659 , -1695),
	// PointF(650 , -1689),
	// PointF(637 , -1690),
	// PointF(629 , -1698),
	// PointF(621 , -1701),
	// PointF(615 , -1692),
	// PointF(608 , -1674),
	// PointF(607 , -1663),
	// PointF(602 , -1654),
	// PointF(600 , -1641),
	// PointF(597 , -1631),
	// PointF(594 , -1621),
	// PointF(591 , -1613),
	// PointF(596 , -1602),
	// PointF(590 , -1594),
	// PointF(590 , -1585),
	// PointF(587 , -1574),
	// PointF(586 , -1565),
	// PointF(586 , -1550),
	// PointF(588 , -1541),
	// PointF(584 , -1531),
	// PointF(570 , -1527),
	// PointF(564 , -1536),
	// PointF(558 , -1524),
	// PointF(550 , -1515),
	// PointF(538 , -1523),
	// PointF(521 , -1532),
	// PointF(511 , -1527),
	// PointF(513 , -1535),
	// PointF(510 , -1526),
	// PointF(500 , -1526),
	// PointF(502 , -1514),
	// PointF(493 , -1512),
	// PointF(484 , -1506),
	// PointF(490 , -1497),
	// PointF(482 , -1495),
	// PointF(480 , -1486),
	// PointF(482 , -1477),
	// PointF(475 , -1469),
	// PointF(482 , -1463),
	// PointF(475 , -1455),
	// PointF(466 , -1446),
	// PointF(457 , -1441),
	// PointF(447 , -1439),
	// PointF(446 , -1431),
	// PointF(433 , -1426),
	// PointF(429 , -1417),
	// PointF(429 , -1408),
	// PointF(419 , -1403),
	// PointF(411 , -1406),
	// PointF(402 , -1411),
	// PointF(393 , -1409),
	// PointF(382 , -1410),
	// PointF(370 , -1406),
	// PointF(360 , -1409),
	// PointF(356 , -1400),
	// PointF(347 , -1399),
	// PointF(337 , -1399),
	// PointF(329 , -1406),
	// PointF(321 , -1409),
	// PointF(310 , -1410),
	// PointF(293 , -1410),
	// PointF(285 , -1407),
	// PointF(276 , -1402),
	// PointF(268 , -1399),
	// PointF(259 , -1396),
	// PointF(252 , -1388),
	// PointF(255 , -1377),
	// PointF(257 , -1369),
	// PointF(260 , -1360),
	// PointF(259 , -1352),
	// PointF(260 , -1338),
	// PointF(268 , -1327),
	// PointF(269 , -1317),
	// PointF(279 , -1309),
	// PointF(288 , -1302),
	// PointF(295 , -1288),
	// PointF(301 , -1278),
	// PointF(300 , -1270),
	// PointF(296 , -1259),
	// PointF(290 , -1250),
	// PointF(287 , -1242),
	// PointF(285 , -1232),
	// PointF(278 , -1222),
	// PointF(269 , -1213),
	// PointF(261 , -1207),
	// PointF(260 , -1215),
	// PointF(247 , -1216),
	// PointF(245 , -1224),
	// PointF(241 , -1231),
	// PointF(232 , -1230),
	// PointF(221 , -1228),
	// PointF(213 , -1220),
	// PointF(200 , -1226),
	// PointF(189 , -1227),
	// PointF(172 , -1224),
	// PointF(164 , -1224),
	// PointF(154 , -1227),
	// PointF(147 , -1235),
	// PointF(137 , -1241),
	// PointF(122 , -1235),
	// PointF(116 , -1243),
	// PointF(107 , -1238),
	// PointF(97 , -1244),
	// PointF(89 , -1243),
	// PointF(95 , -1251),
	// PointF(86 , -1249),
	// PointF(81 , -1258),
	// PointF(72 , -1260),
	// PointF(61 , -1260),
	// PointF(63 , -1268),
	// PointF(71 , -1274),
	// PointF(59 , -1285),
	// PointF(59 , -1292),
	// PointF(50 , -1297),
	// PointF(48 , -1306),
	// PointF(49 , -1315),
	// PointF(40 , -1322),
	// PointF(34 , -1331),
	// PointF(25 , -1331),
	// PointF(29 , -1338),
	// PointF(16 , -1336),
	// PointF(10 , -1327),
	// PointF(7 , -1317),
	// PointF(-1 , -1320),
	// PointF(-3 , -1312),
	// PointF(-11 , -1317),
	// PointF(-21 , -1324),
	// PointF(-22 , -1316),
	// PointF(-21 , -1306),
	// PointF(-30 , -1296),
	// PointF(-39 , -1300),
	// PointF(-39 , -1292),
	// PointF(-44 , -1283),
	// PointF(-46 , -1274),
	// PointF(-44 , -1264),
	// PointF(-51 , -1250),
	// PointF(-57 , -1235),
	// PointF(-60 , -1227),
	// PointF(-60 , -1218),
	// PointF(-54 , -1210),
	// PointF(-65 , -1202),
	// PointF(-60 , -1210),
	// PointF(-73 , -1205),
	// PointF(-80 , -1196),
	// PointF(-85 , -1187),
	// PointF(-89 , -1177),
	// PointF(-96 , -1169),
	// PointF(-100 , -1156),
	// PointF(-104 , -1147),
	// PointF(-113 , -1143),
	// PointF(-122 , -1134),
	// PointF(-130 , -1125),
	// PointF(-139 , -1122),
	// PointF(-135 , -1113),
	// PointF(-140 , -1100),
	// PointF(-149 , -1098),
	// PointF(-148 , -1088),
	// PointF(-153 , -1077),
	// PointF(-161 , -1078),
	// PointF(-157 , -1070),
	// PointF(-170 , -1063),
	// PointF(-178 , -1064),
	// PointF(-187 , -1070),
	// PointF(-197 , -1058),
	// PointF(-203 , -1066),
	// PointF(-212 , -1060),
	// PointF(-220 , -1062),
	// PointF(-225 , -1070),
	// PointF(-240 , -1068),
	// PointF(-242 , -1077),
	// PointF(-234 , -1086),
	// PointF(-229 , -1094),
	// PointF(-221 , -1100),
	// PointF(-219 , -1110),
	// PointF(-215 , -1123),
	// PointF(-217 , -1131),
	// PointF(-206 , -1141),
	// PointF(-210 , -1149),
	// PointF(-210 , -1158),
	// PointF(-210 , -1170),
	// PointF(-220 , -1174),
	// PointF(-224 , -1182),
	// PointF(-231 , -1192),
	// PointF(-232 , -1199),
	// PointF(-238 , -1211),
	// PointF(-245 , -1219),
	// PointF(-250 , -1232),
	// PointF(-254 , -1242),
	// PointF(-259 , -1256),
	// PointF(-263 , -1265),
	// PointF(-267 , -1274),
	// PointF(-269 , -1285),
	// PointF(-269 , -1294),
	// PointF(-270 , -1302),
	// PointF(-279 , -1301),
	// PointF(-290 , -1299),
	// PointF(-299 , -1302),
	// PointF(-295 , -1314),
	// PointF(-294 , -1325),
	// PointF(-301 , -1339),
	// PointF(-303 , -1349),
	// PointF(-302 , -1358),
	// PointF(-300 , -1370),
	// PointF(-299 , -1378),
	// PointF(-296 , -1389),
	// PointF(-288 , -1395),
	// PointF(-286 , -1403),
	// PointF(-279 , -1412),
	// PointF(-275 , -1420),
	// PointF(-270 , -1429),
	// PointF(-266 , -1438),
	// PointF(-266 , -1447),
	// PointF(-281 , -1453),
	// PointF(-291 , -1448),
	// PointF(-298 , -1460),
	// PointF(-303 , -1469),
	// PointF(-302 , -1479),
	// PointF(-302 , -1488),
	// PointF(-315 , -1494),
	// PointF(-324 , -1499),
	// PointF(-325 , -1508),
	// PointF(-318 , -1517),
	// PointF(-320 , -1526),
	// PointF(-327 , -1534),
	// PointF(-335 , -1542),
	// PointF(-341 , -1549),
	// PointF(-342 , -1557),
	// PointF(-341 , -1567),
	// PointF(-342 , -1574),
	// PointF(-350 , -1581),
	// PointF(-355 , -1590),
	// PointF(-365 , -1595),
	// PointF(-369 , -1602),
	// PointF(-363 , -1618),
	// PointF(-366 , -1632),
	// PointF(-371 , -1640),
	// PointF(-380 , -1641),
	// PointF(-388 , -1652),
	// PointF(-388 , -1667),
	// PointF(-387 , -1674),
	// PointF(-385 , -1689),
	// PointF(-386 , -1699),
	// PointF(-385 , -1708),
	// PointF(-383 , -1717),
	// PointF(-382 , -1725),
	// PointF(-385 , -1735),
	// PointF(-400 , -1734),
	// PointF(-413 , -1725),
	// PointF(-420 , -1717),
	// PointF(-424 , -1707),
	// PointF(-425 , -1698),
	// PointF(-433 , -1687),
	// PointF(-442 , -1677),
	// PointF(-449 , -1667),
	// PointF(-458 , -1659),
	// PointF(-467 , -1659),
	// PointF(-476 , -1662),
	// PointF(-485 , -1669),
	// PointF(-479 , -1677),
	// PointF(-471 , -1683),
	// PointF(-480 , -1688),
	// PointF(-487 , -1696),
	// PointF(-485 , -1705),
	// PointF(-481 , -1713),
	// PointF(-476 , -1720),
	// PointF(-481 , -1731),
	// PointF(-492 , -1738),
	// PointF(-500 , -1744),
	// PointF(-501 , -1754),
	// PointF(-501 , -1763),
	// PointF(-513 , -1771),
	// PointF(-522 , -1776),
	// PointF(-531 , -1777),
	// PointF(-537 , -1787),
	// PointF(-548 , -1790),
	// PointF(-557 , -1791),
	// PointF(-565 , -1799),
	// };

	PointF fox_pts[] = {
		PointF(x+30, y), 
		PointF(x, y+50), 
		PointF(x+55, y+100), 
		PointF(x+110, y+50), 
		PointF(x+80, y),
		PointF(x+70, y+25),
		PointF(x+40, y+25)
	};


	graphics->FillPolygon(&brush, fox_pts, 7);
	graphics->DrawPolygon(&pen, fox_pts, 7);
	//

	graphics->~Graphics();


	return 0;
}
