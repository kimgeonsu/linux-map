#pragma once

#include <stdio.h>
#include <string>
#include <math.h>

typedef struct tagKW
{
	short kd;
	short kb;
	double kc;
	short wd;
	short wb;
	double wc;
}KW;

typedef struct tagTM
{
	double x;
	double y;
}TM;

typedef struct tagUTM
{
	double x;
	double y;
}UTM;

#define WGS_84	0
#define BESSEL  1

class CGeoCoordinate
{
public:
	void GetBesselTawon2WGSXY(double sphi, double slam, double& y, double& x);

	bool	mgrs2gp(int tawon, std::string mgrs, KW& kw);
	bool	mgrs2utm(int tawon, std::string mgrs, double& utmx, double& utmy);

	std::string gp2mgrs(int tawon, double lat, double lon);
	std::string utm2mgrs(int tawon, int zone, double tutmx, double tutmy);

	void	GetDatumTransform(int tawon, double alat, double alon, double h, double* tlat, double* tlon, double* th);
	void	GetTawon2utm(int tawon, double sphi, double slam, int* izone, double* y, double* x, int ifixz);
	void	GetUtm2Tawon(int tawon, double* sphi, double* slam, int izone, double y, double x);

	double	GetRadian(short dd, short mm, double ss);
	//junga
	void GetWGSTawon2BesselXY(double sphi, double slam, double& y, double& x);
	//end 
	void	GetDMS(double radian, short* dd, short* mm, double* ss);

	void	GetDegreebyKw(KW kw, double* wd, double* kd);
	void	GetKwbyXY(double wd, double kd, KW* kw);

	double _dCentralKd;
	double _dScalingWd;
	double _dFactor;
	double _dFalseNorth;
	double _dFalseEast;

	void GetTMToKW(double x, double y, KW* kw);
	void GetKWToTM(KW kw, TM* tm);

	CGeoCoordinate();
	~CGeoCoordinate();

	double		m_phi; //0916 junga
private:
	//double m_phi ; //origin
	double		m_radian;
	std::string		m_MGRSText;
	std::string		m_MGRSTextY;
};