/*******************************************************************************/
/* UTM - Ellipsoid Coordinates transforms                                      */
/* (c) 2006 by Stefanos Kozanis, N.T.U.A.                                      */
/* Distributed freely as a Public Domain software                              */
/*                                                                             */
/*******************************************************************************/

/* corefuncs.cpp: Core mathematical functions
*/

#include <math.h>
#include <errno.h>
#include "main_types.h"
#include "corefuncs.h"

void philambda_to_xyz(double phi, double lambda, double *x, double *y, double *z, GSTYPE gstype)
{
	*x = ellipsoid_main_normal_section_radius(phi, gstype)*cos(phi)*cos(lambda);
	*y = ellipsoid_main_normal_section_radius(phi, gstype)*cos(phi)*sin(lambda);
	*z = ellipsoid_main_normal_section_radius(phi, gstype)*(1-get_e2(gstype))*sin(phi);
}

void sphere_xyz_to_philambda(double x, double y, double z, double *phi, double *lambda, double radius)
{
	if(fabs(z)<radius)
		*phi = asin(z/radius);
	else
		if(z>0)
			*phi = 0.5*PI;
		else
			*phi = -0.5*PI;
	if(fabs(x)>0.001)
		*lambda = atan(y/x);
	else
		if(y>0)
			*lambda = 0.5*PI;
		else
			*lambda = -0.5*PI;
	if(x<0)
		*lambda = PI - *lambda;
}

void ellipsoid_xyz_to_philambda(double x, double y, double z, double *phi, double *lambda, GSTYPE gstype)
{
	double aradius, aradius_old;
	int acount;
	aradius = ellipsoids[geodetic_systems[gstype].ellipsoid].Big_Semiaxis;
	sphere_xyz_to_philambda(x, y, z, phi, lambda, aradius);
    *phi = atan( z*(1+get_et2(gstype)) / sqrt(x*x+y*y) );
    acount = 0;
	do{
		acount++;
		aradius_old = aradius;
		aradius = ellipsoid_main_normal_section_radius(*phi, gstype);
		*phi = atan( (z+get_e2(gstype)*aradius*sin(*phi)) / sqrt(x*x+y*y) );
	}while(fabs(aradius-aradius_old)>0.00005&&acount<100);

}

double ellipsoid_arc(double phi, GSTYPE gstype)
{
	double e2, BigSemiaxis;
	double M0, M2, M4, M6, M8;
	double e4, e6, e8;
	BigSemiaxis = ellipsoids[geodetic_systems[gstype].ellipsoid].Big_Semiaxis;
	e2 = get_e2(gstype);
	e4 = e2 * e2;
	e6 = e4 * e2;
	e8 = e6 * e2;
	M0 = 1 + 0.75*e2 + 0.703125*e4 + 0.68359375*e6 + 0.67291259765625*e8; 
	M2 = 0.375*e2 + 0.46875*e4 + 0.5126953125*e6 + 0.538330078125*e8;
	M4= 0.05859375*e4 + 0.1025390625*e6 + 0.25*e8;
	M6= 0.01139322916666667*e6 + 0.025634765625*e8;
	M8= 0.002408551504771226*e8;
	return BigSemiaxis*(1-e2)*(M0*phi-M2*sin(2*phi)+M4*sin(4*phi)-
	  M6*sin(6*phi)+M8*sin(8*phi));
}

double ellipsoid_main_normal_section_radius(double phi, GSTYPE gstype)
{
	double BigSemiaxis, e2;
	BigSemiaxis = ellipsoids[geodetic_systems[gstype].ellipsoid].Big_Semiaxis;
    e2 = get_e2(gstype);
	return BigSemiaxis/sqrt(1-e2*sin(phi)*sin(phi));
}

double ellipsoid_meridian_radius(double phi, GSTYPE gstype)
{
	double BigSemiaxis, e2;
	BigSemiaxis = ellipsoids[geodetic_systems[gstype].ellipsoid].Big_Semiaxis;
    e2 = get_e2(gstype);
	return BigSemiaxis*(1-e2)/pow(1-e2*sin(phi)*sin(phi), 1.5);
}

double get_e2(GSTYPE gstype)
{
	return 1 - pow(1 - (1/ellipsoids[geodetic_systems[gstype].ellipsoid].InvF), 2);
}

double get_et2(GSTYPE gstype)
{
	double f;
	f = 1/ellipsoids[geodetic_systems[gstype].ellipsoid].InvF;
	return get_e2(gstype)/((1-f)*(1-f));
}

double fit(double aphi, PCTYPE pctype)
{
	double l, phi0, phi0_old;
	int acount;
	GSTYPE gstype;

	gstype = pc_systems[pctype].gstype;
	l = aphi/pc_systems[pctype].kappa0;             
	phi0=l/ellipsoids[geodetic_systems[gstype].ellipsoid].Big_Semiaxis;            
	acount = 0;
	do{
		acount++;
		phi0_old = phi0;
		phi0 = phi0 + (l - ellipsoid_arc(phi0, gstype))/
			ellipsoid_main_normal_section_radius(phi0, gstype);
	}while(fabs(phi0-phi0_old)>1e-17 && acount<100 );
	return phi0;
}

void helmert_transform(double x, double y, double z, double *x2, double *y2, double *z2, GSTYPE gstype, double factor)
{
	double dx, dy, dz, rx, ry, rz, m;

	rx = geodetic_systems[gstype].RX*factor;
	ry = geodetic_systems[gstype].RY*factor;
	rz = geodetic_systems[gstype].RZ*factor;
	m  = (1.000 + geodetic_systems[gstype].DS*factor);
	dx = geodetic_systems[gstype].DX*factor;
	dy = geodetic_systems[gstype].DY*factor;
	dz = geodetic_systems[gstype].DZ*factor;
		
    *x2 = (x-rz*y+ry*z)*m + dx;
	*y2 = (rz*x+y-rx*z)*m + dy;
	*z2 = (-ry*x+rx*y+z)*m + dz;
}

void displace_geocentric_system(double x, double y, double z, double *x2, double *y2, double *z2, GSTYPE source, GSTYPE dest)
{
	double xt, yt, zt;
    helmert_transform(x, y, z, &xt, &yt, &zt, source, 1.000);
    helmert_transform(xt, yt, zt, x2, y2, z2, dest, -1.000);
}
