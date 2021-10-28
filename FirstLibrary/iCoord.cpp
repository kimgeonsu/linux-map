#include "iCoord.h"
#include <math.h>
#include <format>

long g_FactorTable[10][3] =
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

CGeoCoordinate::CGeoCoordinate()
{
	m_phi = 4 * atan(1);
	m_radian = m_phi / 180.0;

	m_MGRSText = "ABCDEFGHJKLMNPQRSTUVWXYZABCDEFG";
	m_MGRSTextY = "ABCDEFGHJKLMNPQRSTUVABCDEFG";

	// Tm variables
	_dCentralKd = 127.0;
	_dScalingWd = 38.0;
	_dFactor = 0.9996;
	_dFalseNorth = 500000.0;
	_dFalseEast = 200000.0;
}

CGeoCoordinate::~CGeoCoordinate()
{

}


void CGeoCoordinate::GetDegreebyKw(KW kw, double* wd, double* kd)
{
	*kd = kw.kd + kw.kb / 60.0 + kw.kc / 3600.0;
	*wd = kw.wd + kw.wb / 60.0 + kw.wc / 3600.0;
}

void CGeoCoordinate::GetKwbyXY(double wd, double kd, KW* kw)
{
	kw->wd = (short)wd;
	kw->wb = (short)((wd - kw->wd) * 60.0);
	kw->wc = (double)(((wd - kw->wd) * 60.0 - kw->wb) * 60.0);

	kw->kd = (short)kd;
	kw->kb = (short)((kd - kw->kd) * 60.0);
	kw->kc = (double)(((kd - kw->kd) * 60.0 - kw->kb) * 60.0);
}

void CGeoCoordinate::GetDMS(double radian, short* dd, short* mm, double* ss)
{
	double degree = radian * 180.0 / m_phi;
	*dd = (short)degree;
	*mm = (short)((degree - *dd) * 60.0);
	*ss = (double)(((degree - *dd) * 60.0 - *mm) * 60.0);
}

double CGeoCoordinate::GetRadian(short dd, short mm, double ss)
{
	double degree = dd + mm / 60.0 + ss / 3600.0;
	return (degree * m_phi / 180.0);
}

void CGeoCoordinate::GetDatumTransform(int tawon, double alat, double alon, double h, double* tlat, double* tlon, double* th)
{
	double slat, clat, slon, clon, ssqlat, adb, rn, rm;
	double a, f, esq, da, df, dx, dy, dz;

	if (tawon == BESSEL)
	{
		a = 6377397.155;
		f = 1. / 299.1528128;
		esq = 2. * f - f * f;
		da = 6378137. - 6377397.155;
		df = 1. / 298.257223563 - 1. / 299.1528128;
		dx = -146;
		dy = 507;
		dz = 687;
	}
	else if (tawon == WGS_84)
	{
		a = 6378137.;
		f = 1. / 298.257223563;
		esq = 2. * f - f * f;
		da = -1. * (6378137. - 6377397.155);
		df = -1. * (1. / 298.257223563 - 1. / 299.1528128);
		dx = 146;
		dy = -507;
		dz = -687;
	}

	slat = sin(alat);
	clat = cos(alat);

	slon = sin(alon);
	clon = cos(alon);
	ssqlat = slat * slat;
	adb = 1. / (1. - f);

	rn = a / sqrt(1. - esq * ssqlat);
	rm = a * (1. - esq) / pow(1. - esq * ssqlat, 1.5);

	*tlat = -dx * slat * clon - dy * slat * slon + dz * clat;
	*tlat = *tlat + da * (rn * esq * slat * clat) / a;
	*tlat = *tlat + df * (rm * adb + rn / adb) * slat * clat;
	*tlat = *tlat / (rm + h);

	*tlon = (-dx * slon + dy * clon) / ((rn + h) * clat);

	*tlat = *tlat + alat;
	*tlon = *tlon + alon;

	*th = dx * clat * clon + dy * clat * slon + dz * slat;
	*th = *th - da * a / rn + df * rn * ssqlat / adb;
}

void CGeoCoordinate::GetTawon2utm(int tawon, double sphi, double slam, int* izone, double* y, double* x, int ifixz)
{
	double fe, ok, degrad, recf, es, ebs, tn, ap, bp, cp, dp, ep;
	double olam, dlam, s, c, t, eta, sn, tmd, b, a, f;
	double t1, t2, t3, t4, t5, t6, t7, t8, t9, nfn;

	if (tawon == BESSEL)
	{
		a = 6377397.155;
		f = 1. / 299.1528128;
	}
	else if (tawon == WGS_84)
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

void CGeoCoordinate::GetUtm2Tawon(int tawon, double* sphi, double* slam, int izone, double y, double x)
{
	double fe, ok, degrad, recf, es, ebs, tn, ap, bp, cp, dp, ep;
	double olam, dlam, s, c, t, eta, sn, tmd, b, sr, ftphi, de, a, f;
	double t10, t11, t12, t13, t14, t15, t16, t17, nfn;
	int i;

	if (tawon == BESSEL)
	{
		a = 6377397.155;
		f = 1. / 299.1528128;
	}
	else if (tawon == WGS_84)
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

void CGeoCoordinate::GetTMToKW(double x, double y, KW* kw)
{
	double py, px, p, pr, cc, of, oa, ob, ne, nea, ia;
	double lba, ib, lb, iab, lva, ixx, il, iyy, ix2, iy2;
	double ax1, ax3, ix4, ay1, ay3, iy4;
	double para = _dCentralKd;

	py = (y - _dFalseNorth);
	px = (x - _dFalseEast);

	p = 3.141592654;
	pr = p / 180.0;

	cc = _dScalingWd;

	of = 180.0 / p;
	oa = 6377397.155;
	ob = 6356078.96325;
	ne = (oa * oa - ob * ob) / (oa * oa);
	nea = (oa * oa - ob * ob) / (ob * ob);

	ia = of * pow(1.0 - ne * (sin(cc * pr) * sin(cc * pr)), 1.5) / oa / (1.0 - ne);
	lba = cc + ia * py;
	ib = of * pow(1.0 - ne * (sin((lba + cc) / 2.0 * pr) * sin((lba + cc) / 2.0 * pr)), 1.5) / oa / (1.0 - ne);
	lb = cc + ib * py;
	iab = of * pow(1.0 - ne * (sin(lb * pr)) * (sin(lb * pr)), 0.5) / oa;
	lva = 1.0 + nea * (cos(lb * pr)) * (cos(lb * pr));
	ixx = lb - (iab * px) * (iab * px) * lva / 2.0 / of * tan(lb * pr);
	il = iab * px / cos(lb * pr) - pow((iab * px), 3.0) / 6.0 / (of * of) / cos(lb * pr) * (1.0 + 2.0 * (tan(lb * pr)) * (tan(lb * pr)));
	iyy = para + il;

	ax1 = floor(ixx);
	ix2 = (ixx - ax1) * 60.0;
	ax3 = floor(ix2);
	ix4 = (ix2 - ax3) * 60.0;
	ay1 = floor(iyy);
	iy2 = (iyy - ay1 + 0.0028902778) * 60.0;
	ay3 = floor(iy2);
	if (ay3 == 60.0)
	{
		ay1 = ay1 + 1.0;
		ay3 = 0.0;
		iy4 = (iy2 - 60.0) * 60.0;
	}
	else
	{
		iy4 = (iy2 - ay3) * 60.0;
	}
	kw->wd = (int)ax1;
	kw->wb = (int)ax3;
	kw->wc = (float)ix4;
	kw->kd = (int)ay1;
	kw->kb = (int)ay3;
	kw->kc = (float)iy4;
}

void CGeoCoordinate::GetKWToTM(KW kw, TM* tm)
{
	double jc, ica, iac, icb, ibc, jo, p, pr, ofa, jnn;
	double of, oa, ne, nea, ks, kc, la, lv, lb, ls, lm, ns, nc, na, nk, nt;
	double ba, bb, jbc, aa, ab, jac, tx, ty;
	double para = _dCentralKd;

	ba = (double)kw.kd;
	bb = (double)kw.kb;
	jbc = kw.kc;
	aa = (double)kw.wd;
	ab = (double)kw.wb;
	jac = kw.wc;

	jc = jbc - 10.405;
	ica = ab / 60.0;
	iac = jac / 3600.0;
	icb = bb / 60.0;
	ibc = jc / 3600.0;
	jnn = aa + ica + iac;
	jo = ba + icb + ibc;

	p = 3.141592654;
	pr = 0.0174532925;
	ofa = 0.0087266462;
	of = 57.29577951;
	oa = 6377397.155;
	ne = 0.006674372177;
	nea = 0.006719218744;

	ks = sin(pr * jnn);
	kc = cos(pr * jnn);
	la = jo - para;
	lv = 1.0 + nea * kc * kc;
	lb = jnn + lv * la * la * ofa * ks * kc;
	ls = sin((lb + _dScalingWd) * pr / 2.0);
	lm = oa * (1.0 - ne) / pow((1.0 - ne * ls * ls), 1.5);

	ty = (lb - _dScalingWd) * lm / of + _dFalseNorth;

	ns = sin(lb * pr);
	nc = cos(2.0 * jnn * pr);
	na = oa / pow((1.0 - ne * ns * ns), 0.5);
	nk = of / na;
	nt = pow((6.0 * (180.0 / p) * (180.0 / p)), (-1.0));
	tx = la / nk * kc + la * la * la / nk * nt * kc * nc + _dFalseEast;

	tm->x = tx;
	tm->y = ty;
}

void CGeoCoordinate::GetWGSTawon2BesselXY(double sphi, double slam, double& y, double& x)
{
	double th;
	double tlat;
	double tlon;

	//wgs_84....bessel로...
	GetDatumTransform(WGS_84, sphi, slam, 1, &tlat, &tlon, &th);

	y = tlat * 180. / m_phi;
	x = tlon * 180. / m_phi;
}

void CGeoCoordinate::GetBesselTawon2WGSXY(double sphi, double slam, double& y, double& x)
{
	double th;
	double tlat;
	double tlon;

	//wgs_84....bessel로...
	GetDatumTransform(BESSEL, sphi, slam, 1, &tlat, &tlon, &th);

	y = tlat * 180. / m_phi;
	x = tlon * 180. / m_phi;
}


std::string CGeoCoordinate::gp2mgrs(int tawon, double lat, double lon)
{
	std::string		retValue;
	std::string		zoneValue;
	std::string		zoneSubValue;
	std::string		gridValue;
	KW			tmpKW;
	double		slam = 0.;	// Longitude
	double		sphi = 0.;	// Latitude
	int			tmpZone = 0;
	double		tutmx = 0.;
	double		tutmy = 0.;

	long		xIdx = 0;
	long		yIdx = 0;
	long		mgrsx = 0;
	long		mgrsy = 0;

	long		stateValue = 0;
	long		xIdxGrid = 0;
	long		yIdxGrid = 0;

	GetKwbyXY(lat, lon, &tmpKW);

	yIdx = tmpKW.wd / 8;
	xIdx = tmpKW.kd / 6;
	zoneValue = xIdx + 31;
	zoneSubValue = yIdx + 12;

	_dCentralKd = 127;
	slam = GetRadian(tmpKW.kd, tmpKW.kb, tmpKW.kc);	// 경도
	sphi = GetRadian(tmpKW.wd, tmpKW.wb, tmpKW.wc);	// 위도

	GetTawon2utm(tawon, sphi, slam, &tmpZone, &tutmy, &tutmx, 0);

	// Grid Value Calculate
	yIdx = (long)(tutmy / 100000.);
	mgrsy = (long)(tutmy - (yIdx * 100000.));
	yIdx %= 20;
	xIdx = (long)(tutmx / 100000.);
	mgrsx = (long)(tutmx - (xIdx * 100000.));

	xIdx--;	// 1 Base Idx

	if (xIdx < 0)
		xIdx = 0;

	stateValue = (tmpZone - 1) % 3;
	xIdxGrid = (8 * stateValue) + xIdx;

	stateValue = (tmpZone - 1) % 2;
	yIdxGrid = (5 * stateValue) + yIdx;
	gridValue = xIdxGrid + yIdxGrid;

	//retValue.Format(TEXT("%s%s %s %05d %05d"), zoneValue, zoneSubValue, gridValue, mgrsx, mgrsy);
	retValue = zoneSubValue + zoneSubValue + " " + gridValue + " " + std::to_string(mgrsx) + " " + std::to_string(mgrsy);
	return retValue;
}

bool CGeoCoordinate::mgrs2gp(int tawon, std::string mgrs, KW& kw)
{
	std::string		tEnd;
	std::string		xValue;
	std::string		yValue;
	std::string		xGrid;
	std::string		yGrid;
	std::string		zoneValue;
	std::string		zoneSubValue;
	std::string		subString;

	long		Factor = 0;
	long		ixValue = 0;
	long		iyValue = 0;
	long		xIdx = 0;
	long		yIdx = 0;
	long		subIdx = 0;
	long		strartIdx = 0;
	long		izondValue = 0;

	double		utmx;
	double		utmy;
	double		slam;
	double		sphi;

	for (int i = 0; i < mgrs.size(); i++) {
		mgrs[i] = toupper(mgrs[i]);
	}
	mgrs.replace(mgrs.find(" "), mgrs.length(), "");

	if (mgrs.length() < 5)
		return false;

	zoneValue = mgrs[0] + mgrs[1];
	izondValue = (long)_tcstod(zoneValue, &tEnd);

	zoneSubValue = mgrs[2];
	xGrid = mgrs[3];
	yGrid = mgrs[4];

	if (mgrs.length() > 5)
	{
		subString = mgrs.substr(mgrs.length()-1 ,mgrs.length() - 5);
		switch (subString.length())
		{
		case 2:
			Factor = 10000;
			xValue = subString[0];
			yValue = subString.substr(subString.length() - 1, 1);
			break;
		case 4:
			Factor = 1000;
			xValue = subString.substr(0,2);
			yValue = subString.substr(subString.length() - 1, 2);
			break;
		case 6:
			Factor = 100;
			xValue = subString.substr(0,3);
			yValue = subString.substr(subString.length() - 1, 3);
			break;
		case 8:
			Factor = 10;
			xValue = subString.substr(0,4);
			yValue = subString.substr(subString.length() - 1, 4);
			break;
		case 10:
			Factor = 1;
			xValue = subString.substr(0,5);
			yValue = subString.substr(subString.length() - 1, 5);
			break;
		default:
			return false;
			break;
		}

		ixValue = (long)_tcstod(xValue, &tEnd);
		iyValue = (long)_tcstod(yValue, &tEnd);

		ixValue *= Factor;
		iyValue *= Factor;
	}
	else
	{
		subString.clear();
		Factor = 0;
		ixValue = 0;
		iyValue = 0;
	}

	subIdx = m_MGRSText.find(zoneSubValue);
	subIdx = subIdx - 12;

	strartIdx = ((izondValue - 1) % 3) * 8;
	xIdx = m_MGRSText.find(xGrid, strartIdx);
	xIdx++;							// 1 Base Idx
	xIdx -= strartIdx;

	strartIdx = ((izondValue - 1) % 2) * 5;
	yIdx = m_MGRSTextY.find(yGrid, strartIdx);
	yIdx -= strartIdx;

	utmx = (xIdx * 100000.) + ixValue;
	utmx += 0.5;

	if (yIdx > g_FactorTable[subIdx][0])
		Factor = g_FactorTable[subIdx][1];
	else
		Factor = g_FactorTable[subIdx][2];

	utmy = (Factor * 1000000) + (yIdx * 100000.) + iyValue;
	utmy += 0.5;

	GetUtm2Tawon(tawon, &sphi, &slam, izondValue, utmy, utmx);
	GetDMS(sphi, &kw.wd, &kw.wb, &kw.wc);
	GetDMS(slam, &kw.kd, &kw.kb, &kw.kc);

	return true;
}

std::string CGeoCoordinate::utm2mgrs(int tawon, int zone, double tutmx, double tutmy)
{
	std::string		retValue;
	std::string		zoneValue;
	std::string		zoneSubValue;
	std::string		gridValue;
	KW			tmpKW;
	double		slam = 0.;	// Longitude
	double		sphi = 0.;	// Latitude
	int			tmpZone = 0;

	long		xIdx = 0;
	long		yIdx = 0;
	long		mgrsx = 0;
	long		mgrsy = 0;

	long		stateValue = 0;
	long		xIdxGrid = 0;
	long		yIdxGrid = 0;

	GetUtm2Tawon(tawon, &sphi, &slam, zone, tutmy, tutmx);
	GetDMS(sphi, &tmpKW.wd, &tmpKW.wb, &tmpKW.wc);
	GetDMS(slam, &tmpKW.kd, &tmpKW.kb, &tmpKW.kc);

	yIdx = tmpKW.wd / 8;
	xIdx = tmpKW.kd / 6;
	zoneValue = xIdx + 31;
	zoneSubValue = m_MGRSText[yIdx + 12];

	// Grid Value Calculate
	yIdx = (long)(tutmy / 100000.);
	mgrsy = (long)(tutmy - (yIdx * 100000.));
	yIdx %= 20;
	xIdx = (long)(tutmx / 100000.);
	mgrsx = (long)(tutmx - (xIdx * 100000.));

	xIdx--;	// 1 Base Idx

	if (xIdx < 0)
		xIdx = 0;

	stateValue = (zone - 1) % 3;
	xIdxGrid = (8 * stateValue) + xIdx;

	stateValue = (zone - 1) % 2;
	yIdxGrid = (5 * stateValue) + yIdx;
	gridValue = m_MGRSText[xIdxGrid] + m_MGRSTextY[yIdxGrid];

	if (mgrsx < 0)
		mgrsx = -mgrsx;
	if (mgrsy < 0)
		mgrsy = -mgrsy;
	//retValue.Format(TEXT("%s%s %s %05d %05d"), zoneValue, zoneSubValue, gridValue, mgrsx, mgrsy);
	retValue = zoneSubValue + zoneSubValue + " " + gridValue + " " + std::to_string(mgrsx) + " " + std::to_string(mgrsy);

	return retValue;
}

bool CGeoCoordinate::mgrs2utm(int tawon, std::string mgrs, double& utmx, double& utmy)
{
	std::string* tEnd;
	std::string		xValue;
	std::string		yValue;
	std::string		xGrid;
	std::string		yGrid;
	std::string		zoneValue;
	std::string		zoneSubValue;
	std::string		subString;

	long		Factor = 0;
	long		ixValue = 0;
	long		iyValue = 0;
	long		xIdx = 0;
	long		yIdx = 0;
	long		subIdx = 0;
	long		strartIdx = 0;
	long		izondValue = 0;

	for (int i = 0; i < mgrs.size(); i++) {
		mgrs[i] = toupper(mgrs[i]);
	}
	mgrs.replace(mgrs.find(" "), mgrs.length(), "");

	if (mgrs.length() < 5)
		return false;

	zoneValue = mgrs[0] + mgrs[1];
	izondValue = (long)_tcstod(zoneValue, &tEnd);

	zoneSubValue = mgrs[2];
	xGrid = mgrs[3];
	yGrid = mgrs[4];

	if (mgrs.length() > 5)
	{
		subString = mgrs.substr(subString.length() -1,mgrs.length() - 5);
		switch (subString.length())
		{
		case 2:
			Factor = 10000;
			xValue = subString[0];
			yValue = subString.substr(subString.length() -1,1);
			break;
		case 4:
			Factor = 1000;
			xValue = subString.substr(0,2);
			yValue = subString.substr(subString.length() -1,2);
			break;
		case 6:
			Factor = 100;
			xValue = subString.substr(0,3);
			yValue = subString.substr(subString.length() -1,3);
			break;
		case 8:
			Factor = 10;
			xValue = subString.substr(0,4);
			yValue = subString.substr(subString.length() -1,4);
			break;
		case 10:
			Factor = 1;
			xValue = subString.substr(0,5);
			yValue = subString.substr(subString.length() -1,5);
			break;
		default:
			return false;
			break;
		}

		ixValue = (long)_tcstod(xValue, &tEnd);
		iyValue = (long)_tcstod(yValue, &tEnd);

		ixValue *= Factor;
		iyValue *= Factor;
	}
	else
	{
		subString.clear();
		Factor = 0;
		ixValue = 0;
		iyValue = 0;
	}

	subIdx = m_MGRSText.find(zoneSubValue);
	subIdx = subIdx - 12;

	strartIdx = ((izondValue - 1) % 3) * 8;
	xIdx = m_MGRSText.find(xGrid, strartIdx);
	xIdx++;							// 1 Base Idx
	xIdx -= strartIdx;

	strartIdx = ((izondValue - 1) % 2) * 5;
	yIdx = m_MGRSTextY.find(yGrid, strartIdx);
	yIdx -= strartIdx;

	utmx = (xIdx * 100000.) + ixValue;
	utmx += 0.5;

	if (yIdx >= g_FactorTable[subIdx][0])
		Factor = g_FactorTable[subIdx][1];
	else
		Factor = g_FactorTable[subIdx][2];

	utmy = (Factor * 1000000) + (yIdx * 100000.) + iyValue;
	utmy += 0.5;

	return true;
}