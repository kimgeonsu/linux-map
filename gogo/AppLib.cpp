// AppLib.cpp: implementation of the CAppLib class.
//
//////////////////////////////////////////////////////////////////////

#include "AppLib.h"
#include "MapType.h"

#include <algorithm>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAppLib::CAppLib()
{

}

CAppLib::~CAppLib()
{

}

double CAppLib::GetDistance(_dPoint a, _dPoint b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Coordinate Conversion

void CAppLib::Coord_GetDegreebyDMS(_LatLonDMS latlonDMS, _dPoint& latlon)
{
	latlon.x = latlonDMS.LonDo + latlonDMS.LonBun / 60.0 + latlonDMS.LonCho / 3600.0;
	latlon.y = latlonDMS.LatDo + latlonDMS.LatBun / 60.0 + latlonDMS.LatCho / 3600.0;
}

void CAppLib::Coord_GetDMSbyDegree(_dPoint latlon, _LatLonDMS& latlonDMS)
{
	latlonDMS.LatDo = (short)latlon.y;
	latlonDMS.LatBun = (short)((latlon.y - (double)latlonDMS.LatDo) * 60.0);
	latlonDMS.LatCho = (double)(((latlon.y - (double)latlonDMS.LatDo) * 60.0 - (double)latlonDMS.LatBun) * 60.0);

	latlonDMS.LonDo = (short)latlon.x;
	latlonDMS.LonBun = (short)((latlon.x - (double)latlonDMS.LonDo) * 60.0);
	latlonDMS.LonCho = (double)(((latlon.x - (double)latlonDMS.LonDo) * 60.0 - (double)latlonDMS.LonBun) * 60.0);

}

void CAppLib::Coord_GetDMS(double radian, short& dd, short& mm, double& ss)
{
	double degree = radian * 180.0 / GREEN_MAP_CONST::PI_VALUE;
	dd = (short)degree;
	mm = (short)((degree - dd) * 60.0);
	ss = (double)(((degree - dd) * 60.0 - mm) * 60.0);
}

double CAppLib::Coord_GetRadian(short dd, short mm, double ss)
{
	double degree = dd + mm / 60.0 + ss / 3600.0;
	return (degree * GREEN_MAP_CONST::PI_VALUE / 180.0);
}

bool CAppLib::Coord_MGRS2UTM(std::string mgrs, _dPoint& utmPoint)
{
	int tEnd;
	std::string		xValue;
	std::string		yValue;
	std::string		xGrid;
	std::string		yGrid;
	std::string		zoneValue;
	std::string		zoneSubValue;
	std::string		subString;

	std::string		mgrsString = APPLIB_CONST::MGRSText;
	std::string		mgrsStringY = APPLIB_CONST::MGRSTextY;

	long		Factor = 0;
	long		ixValue = 0;
	long		iyValue = 0;
	long		xIdx = 0;
	long		yIdx = 0;
	long		subIdx = 0;
	long		strartIdx = 0;
	long		izondValue = 0;

	std::transform(mgrs.begin(), mgrs.end(), mgrs.begin(), ::toupper);
	mgrs.erase(remove(mgrs.begin(), mgrs.end(), ' '), mgrs.end());

	if (mgrs.length() < 5)
		return false;

	zoneValue = mgrs[0] + mgrs[1];
	izondValue = (long)stod(zoneValue);

	zoneSubValue = mgrs[2];
	xGrid = mgrs[3];
	yGrid = mgrs[4];
	if (mgrs.length() > 5)
	{
		subString = mgrs.substr(subString.length() - 1, mgrs.length() - 5);
		switch (subString.length())
		{
		case 2:
			Factor = 10000;
			xValue = subString.substr(0, 1);
			yValue = subString.substr(subString.length() - 1, 1);
			break;
		case 4:
			Factor = 1000;
			xValue = subString.substr(0, 2);
			yValue = subString.substr(subString.length() - 1, 2);
			break;
		case 6:
			Factor = 100;
			xValue = subString.substr(0, 3);
			yValue = subString.substr(subString.length() - 1, 3);
			break;
		case 8:
			Factor = 10;
			xValue = subString.substr(0, 4);
			yValue = subString.substr(subString.length() - 1, 4);
			break;
		case 10:
			Factor = 1;
			xValue = subString.substr(0, 5);
			yValue = subString.substr(subString.length() - 1, 5);
			break;
		default:
			return false;
			//break;
		}

		ixValue = (long)stod(xValue);
		iyValue = (long)stod(yValue);

		ixValue *= Factor;
		iyValue *= Factor;
	}
	else
	{
		subString = "";
		Factor = 0;
		ixValue = 0;
		iyValue = 0;
	}

	subIdx = mgrsString.find(zoneSubValue);
	subIdx = subIdx - 12;

	strartIdx = ((izondValue - 1) % 3) * 8;
	xIdx = mgrsString.find(xGrid, strartIdx);
	xIdx++;							// 1 Base Idx
	xIdx -= strartIdx;

	strartIdx = ((izondValue - 1) % 2) * 5;
	yIdx = mgrsStringY.find(yGrid, strartIdx);
	yIdx -= strartIdx;

	utmPoint.x = (xIdx * 100000.) + ixValue;
	utmPoint.x += 0.5;

	if (yIdx >= APPLIB_CONST::FactorTable[subIdx][0])
		Factor = APPLIB_CONST::FactorTable[subIdx][1];
	else
		Factor = APPLIB_CONST::FactorTable[subIdx][2];

	utmPoint.y = (Factor * 1000000) + (yIdx * 100000.) + iyValue;
	utmPoint.y += 0.5;

	return true;
}



std::string CAppLib::Coord_UTM2MGRS(int tawon, int zone, _dPoint utmPoint)
{
	std::string		retValue;
	std::string		zoneValue;
	std::string		zoneSubValue;
	std::string		gridValue;
	_LatLonDMS	latlonDMS;
	double		slam = 0.;	// Longitude
	double		sphi = 0.;	// Latitude

	long		xIdx = 0;
	long		yIdx = 0;
	long		mgrsx = 0;
	long		mgrsy = 0;

	long		stateValue = 0;
	long		xIdxGrid = 0;
	long		yIdxGrid = 0;

	Coord_UTM2Tawon(tawon, &sphi, &slam, zone, utmPoint.y, utmPoint.x);
	Coord_GetDMS(sphi, latlonDMS.LatDo, latlonDMS.LatBun, latlonDMS.LatCho);
	Coord_GetDMS(slam, latlonDMS.LonDo, latlonDMS.LonBun, latlonDMS.LonCho);

	yIdx = latlonDMS.LatDo / 8;
	xIdx = latlonDMS.LonDo / 6;
	zoneValue = (xIdx + 31);
	zoneSubValue = APPLIB_CONST::MGRSText[yIdx + 12];

	// Grid Value Calculate
	yIdx = (long)(utmPoint.y / 100000.);
	mgrsy = (long)(utmPoint.y - (yIdx * 100000.));
	yIdx %= 20;
	xIdx = (long)(utmPoint.x / 100000.);
	mgrsx = (long)(utmPoint.x - (xIdx * 100000.));

	xIdx--;	// 1 Base Idx

	if (xIdx < 0)
		xIdx = 0;

	stateValue = (zone - 1) % 3;
	xIdxGrid = (8 * stateValue) + xIdx;

	stateValue = (zone - 1) % 2;
	yIdxGrid = (5 * stateValue) + yIdx;
	gridValue = APPLIB_CONST::MGRSText[xIdxGrid] + APPLIB_CONST::MGRSTextY[yIdxGrid];

	if (mgrsx < 0)
		mgrsx = -mgrsx;
	if (mgrsy < 0)
		mgrsy = -mgrsy;
	retValue = zoneValue + zoneSubValue + " " + gridValue + " " + std::to_string(mgrsx) + " " + std::to_string(mgrsy);

	return retValue;
}

void CAppLib::Coord_Tawon2UTM(int tawon, double sphi, double slam, int* izone, double* y, double* x, int ifixz)
{
	double fe, ok, degrad, recf, es, ebs, tn, ap, bp, cp, dp, ep;
	double olam, dlam, s, c, t, eta, sn, tmd, b, a, f;
	double t1, t2, t3, t4, t5, t6, t7, t8, t9, nfn;

	if (tawon == GREEN_MAP_CONST::MAP_COORD_TYPE::BESSEL_TYPE)
	{
		a = 6377397.155;
		f = 1. / 299.1528128;
	}
	else
	{
		a = 6378137.;
		f = 1. / 298.257223563;
	}

	fe = 500000;
	ok = 0.9996;
	degrad = atan(1.) / 45.;

	recf = 1. / f;
	b = a * (recf - 1.) / recf;

	es = (a * a - b * b) / (a * a);
	ebs = (a * a - b * b) / (b * b);

	tn = (a - b) / (a + b);
	ap = a * (1. - tn + 5. * (tn * tn - tn * tn * tn) / 4. + 81. * (tn * tn * tn * tn - tn * tn * tn * tn * tn) / 64.);
	bp = 3. * a * (tn - tn * tn + 7. * (tn * tn * tn - tn * tn * tn * tn) / 8. + 55. * tn * tn * tn * tn * tn / 64.) / 2.;
	cp = 15. * a * (tn * tn - tn * tn * tn + 3. * (tn * tn * tn * tn - tn * tn * tn * tn * tn) / 4.) / 16.;
	dp = 35. * a * (tn * tn * tn - tn * tn * tn * tn + 11. * tn * tn * tn * tn * tn / 16.) / 48.;
	ep = 315. * a * (tn * tn * tn * tn - tn * tn * tn * tn * tn) / 512.;

	if (ifixz == 0)
		*izone = 31 + (int)(slam / degrad / 6.);
	if (*izone > 60)
		*izone = 60;
	if (*izone < 1)
		*izone = 1;

	olam = (*izone * 6 - 183) * degrad;
	dlam = slam - olam;

	s = sin(sphi);
	c = cos(sphi);
	t = s / c;
	eta = ebs * c * c;
	sn = a / sqrt(1. - es * sin(sphi) * sin(sphi));
	tmd = ap * sphi - bp * sin(2. * sphi) + cp * sin(4. * sphi) - dp * sin(6. * sphi) + ep * sin(8. * sphi);

	t1 = tmd * ok;
	t2 = sn * s * c * ok / 2.;
	t3 = sn * s * c * c * c * ok * (5. - t * t + 9. * eta + 4. * eta * eta) / 24.;
	t4 = sn * s * c * c * c * c * c * ok * (61. - 58. * t * t + t * t * t * t + 270. * eta - 330. * t * t * eta
		+ 445. * eta * eta + 324. * eta * eta * eta - 680. * eta * eta * t * t + 88. * eta * eta * eta * eta
		- 600. * t * t * eta * eta * eta - 192. * t * t * eta * eta * eta * eta) / 720.;
	t5 = sn * s * c * c * c * c * c * c * c * ok * (1385. - 3111. * t * t + 543. * t * t * t * t - t * t * t * t * t * t) / 40320.;

	nfn = 0;
	if (sphi < 0)	nfn = 10000000.;

	*y = nfn + t1 + dlam * dlam * t2 + dlam * dlam * dlam * dlam * t3
		+ dlam * dlam * dlam * dlam * dlam * dlam * t4
		+ dlam * dlam * dlam * dlam * dlam * dlam * dlam * dlam * t5;

	t6 = sn * c * ok;
	t7 = sn * c * c * c * ok * (1. - t * t + eta) / 6.;
	t8 = sn * c * c * c * c * c * ok * (5. - 18. * t * t + t * t * t * t + 14. * eta - 58. * t * t * eta
		+ 13. * eta * eta + 4. * eta * eta * eta - 64. * eta * eta * t * t - 24. * eta * eta * eta * eta) / 120.;
	t9 = sn * c * c * c * c * c * c * c * ok * (61. - 479. * t * t + 179. * t * t * t * t - t * t * t * t * t * t) / 5040.;
	*x = fe + dlam * t6 + dlam * dlam * dlam * t7 + dlam * dlam * dlam * dlam * dlam * t8
		+ dlam * dlam * dlam * dlam * dlam * dlam * dlam * t9;
}

void	CAppLib::Coord_UTM2Tawon(int tawon, double* sphi, double* slam, int izone, double y, double x)
{
	double fe, ok, degrad, recf, es, ebs, tn, ap, bp, cp, dp, ep;
	double olam, dlam, s, c, t, eta, sn, tmd, b, sr, ftphi, de, a, f;
	double t10, t11, t12, t13, t14, t15, t16, t17, nfn;
	int i;

	if (tawon == GREEN_MAP_CONST::MAP_COORD_TYPE::BESSEL_TYPE)
	{
		a = 6377397.155;
		f = 1. / 299.1528128;
	}
	else
	{
		a = 6378137.;
		f = 1. / 298.257223563;
	}

	fe = 500000;
	ok = 0.9996;
	degrad = atan(1.) / 45.;

	recf = 1. / f;
	b = a * (recf - 1.) / recf;

	es = (a * a - b * b) / (a * a);
	ebs = (a * a - b * b) / (b * b);

	tn = (a - b) / (a + b);
	ap = a * (1. - tn + 5. * (tn * tn - tn * tn * tn) / 4. + 81. * (tn * tn * tn * tn - tn * tn * tn * tn * tn) / 64.);
	bp = 3. * a * (tn - tn * tn + 7. * (tn * tn * tn - tn * tn * tn * tn) / 8. + 55. * tn * tn * tn * tn * tn / 64.) / 2.;
	cp = 15. * a * (tn * tn - tn * tn * tn + 3. * (tn * tn * tn * tn - tn * tn * tn * tn * tn) / 4.) / 16.;
	dp = 35. * a * (tn * tn * tn - tn * tn * tn * tn + 11. * tn * tn * tn * tn * tn / 16.) / 48.;
	ep = 315. * a * (tn * tn * tn * tn - tn * tn * tn * tn * tn) / 512.;

	nfn = 0;
	if (y < 0) {
		nfn = 10000000;
		y = fabs(y);
	}

	*sphi = 0;
	*slam = 0;

	tmd = (y - nfn) / ok;
	sr = a * (1. - es) / ((sqrt(1. - es * sin(*sphi) * sin(*sphi))) * (sqrt(1. - es * sin(*sphi) * sin(*sphi)))
		* (sqrt(1. - es * sin(*sphi) * sin(*sphi))));

	ftphi = tmd / sr;

	for (i = 0; i < 5; i++) {
		t10 = ap * ftphi - bp * sin(2. * ftphi) + cp * sin(4. * ftphi) - dp * sin(6. * ftphi) + ep * sin(8. * ftphi);
		sr = a * (1. - es) / ((sqrt(1. - es * sin(ftphi) * sin(ftphi))) * (sqrt(1. - es * sin(ftphi)
			* sin(ftphi))) * (sqrt(1. - es * sin(ftphi) * sin(ftphi))));
		ftphi += (tmd - t10) / sr;
	}

	sr = a * (1. - es) / ((sqrt(1. - es * sin(ftphi) * sin(ftphi))) * (sqrt(1. - es * sin(ftphi)
		* sin(ftphi))) * (sqrt(1. - es * sin(ftphi) * sin(ftphi))));
	sn = a / sqrt(1. - es * sin(ftphi) * sin(ftphi));

	s = sin(ftphi);
	c = cos(ftphi);
	t = s / c;
	eta = ebs * c * c;

	de = x - fe;

	t10 = t / (2. * sr * sn * ok * ok);
	t11 = t * (5. + 3. * t * t + eta - 4. * eta * eta - 9. * t * t * eta) / (24. * sr * sn * sn * sn * ok * ok * ok * ok);
	t12 = t * (61. + 90. * t * t + 46. * eta + 45. * t * t * t * t - 252. * t * t * eta - 3. * eta * eta + 100. * eta * eta * eta
		- 66. * t * t * eta * eta - 90. * t * t * t * t * eta + 88. * eta * eta * eta * eta + 225. * t * t * t * t * eta * eta
		+ 84. * t * t * eta * eta * eta - 192. * t * t * eta * eta * eta * eta) / (720. * sr * sn * sn * sn * sn * sn * ok * ok * ok * ok * ok * ok);
	t13 = t * (1385. + 3633. * t * t + 4095. * t * t * t * t + 1575. * t * t * t * t * t * t)
		/ (40320. * sr * sn * sn * sn * sn * sn * sn * sn * ok * ok * ok * ok * ok * ok * ok * ok);
	*sphi = ftphi - de * de * t10 + de * de * de * de * t11 - de * de * de * de * de * de * t12 + de * de * de * de * de * de * de * de * t13;

	t14 = 1. / (sn * c * ok);
	t15 = (1. + 2. * t * t + eta) / (6. * sn * sn * sn * c * ok * ok * ok);
	t16 = (5. + 6. * eta + 28. * t * t - 3. * eta * eta + 8. * t * t * eta + 24. * t * t * t * t - 4. * eta * eta * eta + 4. * t * t * eta * eta
		+ 24. * t * t * eta * eta * eta) / (120. * sn * sn * sn * sn * sn * c * ok * ok * ok * ok * ok);
	t17 = (61. + 662. * t * t + 1320. * t * t * t * t + 720. * t * t * t * t * t * t)
		/ (5040. * sn * sn * sn * sn * sn * sn * sn * c * ok * ok * ok * ok * ok * ok * ok);

	dlam = de * t14 - de * de * de * t15 + de * de * de * de * de * t16 - de * de * de * de * de * de * de * t17;
	olam = (izone * 6 - 183) * degrad;
	*slam = olam + dlam;
}
