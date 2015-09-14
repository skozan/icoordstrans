/*******************************************************************************/
/* UTM - Ellipsoid Coordinates transforms                                      */
/* (c) 2006 by Stefanos Kozanis, N.T.U.A.                                      */
/* Distributed freely as a Public Domain software                              */
/*                                                                             */
/*******************************************************************************/

/* Main unit.
*/

#include <math.h>
#include <errno.h>
#ifdef _WINDOWS
  #include <windows.h>
#endif
#include "main_types.h"
#include "icoordstrans.h"
#include "corefuncs.h"

#ifdef _WINDOWS
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}
#endif

EXTERNC int WINAPI hatt_project_philambda_to_xy(double phi, double lambda, double phi0, double lambda0, double *x, double *y, double *gamma, PCTYPE pctype)
{
	double dlambda, dphi, et2, N0, r0, c, s, t;

	et2 = get_et2(pc_systems[pctype].gstype);
	dphi = phi - phi0;
	dlambda = lambda - lambda0;
	c = cos(phi0);
	s = sin(phi0);
	t = tan(phi0);
	N0 = ellipsoid_main_normal_section_radius(phi0, pc_systems[pctype].gstype);
	r0 = ellipsoid_meridian_radius(phi0, pc_systems[pctype].gstype);

    *x = N0*c-r0*s*dphi;
	*x = *x-(1/6.000)*r0*c*(2+9*et2*s*s)*dphi*dphi;
	*x = *x-(1/6.000)*N0*c*s*s*dlambda*dlambda;
	*x = *x * dlambda;
	*y = r0*dphi+0.5*N0*c*s*dlambda*dlambda;
	*y = *y+1.50*r0*r0*et2*s*c*dphi*dphi/N0;
    *y = *y+(1/6.000)*r0*(1-4*s*s+et2*pow(c,4))*dphi*dlambda*dlambda;
	*gamma = t*(*x/N0)+(1/3.000)*(2+3*t*t+2*et2*c*c)*(*x/N0)*(*y/N0);
	*gamma = *gamma + (1/(3.000*c*c*c))*(*x/N0)*(3*pow(*y/N0,2)-pow(*x/N0,2));
	return errno;
}

EXTERNC int WINAPI hatt_project_xy_to_philambda(double x, double y, double phi0, double lambda0, double* phi, double* lambda, double* gamma, PCTYPE pctype)
{
	double t, et2, N0, r0, c, s;

	et2 = get_et2(pc_systems[pctype].gstype);
    t = tan(phi0);
	c = cos(phi0);
	s = sin(phi0);
	N0 = ellipsoid_main_normal_section_radius(phi0, pc_systems[pctype].gstype);
	r0 = ellipsoid_meridian_radius(phi0, pc_systems[pctype].gstype);

    *phi = phi0+y/r0-0.5*t*(x/r0)*(x/N0);
	*phi = *phi-1.5*et2*t*c*c*(y/r0)*(y/N0);
	*phi = *phi-(1/6.000)*(1+3*t*t+et2*c*c-9*et2*s*s)*(y/r0)*pow(x/N0,2);
	*lambda = lambda0+x/(N0*cos(phi0))+(t/c)*(x/N0)*(y/N0);
	*lambda = *lambda+((1+3*t*t+et2*c*c)/(3*c))*(x/N0)*pow(y/N0,2);
	*lambda = *lambda-(t*t/(3*c))*pow(x/N0,3);
	*gamma = t*(x/N0)+(1/3.000)*(2+3*t*t+2*et2*c*c)*(x/N0)*(y/N0);
	*gamma = *gamma + (1/(3.000*c*c*c))*(x/N0)*(3*pow(y/N0,2)-pow(x/N0,2));
	return errno;
}

EXTERNC int WINAPI utm_project_philambda_to_xy(double phi, double lambda, double *x, double *y, double *gamma, PCTYPE pctype)
{
	double t, n2, L, dl, Ni, Mi;
	double e2, kappa0;
	GSTYPE gstype;

    gstype = pc_systems[pctype].gstype;      
	kappa0 = pc_systems[pctype].kappa0; 
	e2 = get_e2(gstype);
	*x = 0;
	*y = 0;
	dl = lambda - pc_systems[pctype].lambda0;
    t = tan(phi);
	n2 = e2*cos(phi)*cos(phi)/(1-e2);
	L = dl*cos(phi);
	Ni = ellipsoid_main_normal_section_radius(phi, gstype);
	Mi = ellipsoid_arc(phi, gstype);
	*x= (((5-18*t*t+t*t*t*t+14*n2-58*t*t*n2)*L*L/120.00 + (1-t*t+n2)/6.00)*L*L+1)*
	     L*kappa0*Ni + pc_systems[pctype].xoffset;
	*y= Mi + (Ni*t/2)*L*L + (Ni*t/24)*(5-t*t+9*n2+4*n2*n2)*L*L*L*L +
	  (Ni*t/720)*(61-58*t*t)*L*L*L*L*L*L;
	*y = *y*kappa0 + pc_systems[pctype].yoffset;
	*gamma = t*L+t*L*L*L*(1+3*n2+4*n2*n2)/3+t*(2-t*t)*L*L*L*L*L/15;
	return errno;
}

EXTERNC int WINAPI utm_project_xy_to_philambda(double x, double y, double *phi, double *lambda, double *gamma, PCTYPE pctype)
{
	double t, n2, f0, N0, P, P2;
	double kappa0;
	GSTYPE gstype;

    gstype = pc_systems[pctype].gstype;      
    kappa0 = pc_systems[pctype].kappa0;
	*phi = 0;
	*lambda = 0;
	x = x-pc_systems[pctype].xoffset;
	y = y-pc_systems[pctype].yoffset;
	f0=fit(y, pctype);
	N0=ellipsoid_main_normal_section_radius(f0, gstype);
    t = tan(f0);
	n2 = get_et2(gstype)*cos(f0)*cos(f0);
	P=(x/(kappa0*N0));
	P2=P*P;
		
	*phi = (((-(61+90*t*t+45*t*t*t*t)*P2/720 +
	   (5+3*t*t+6*n2-3*n2*n2-6*t*t*n2-9*t*t*n2*n2)/24)*P2-
	   (1+n2)/2)*P2)*t + f0;

	*lambda = ((((5+6*n2+28*t*t+8*t*t*n2+24*t*t*t*t)*P2/120 -
		(1+2*t*t+n2)/6)*P2+1)*P)/cos(f0) + pc_systems[pctype].lambda0;

	*gamma=x*t/(kappa0*N0)-t*(1+t*t-n2-2*n2*n2)*x*x*x/(3*kappa0*kappa0*kappa0*N0*N0*N0)+
		t*(2+5*t*t+3*t*t*t*t)*pow(x/(kappa0*N0),5)/15;

	return errno;
}

EXTERNC int WINAPI project_philambda_to_xy(double phi, double lambda, double *x, double *y, double *gamma, PCTYPE pctype)
{ 
	switch(pc_systems[pctype].prjtype){
	case PT_UTM:
		return utm_project_philambda_to_xy(phi, lambda, x, y, gamma, pctype); 
	case PT_HATT:
		return hatt_project_philambda_to_xy(phi, lambda, pc_systems[pctype].phi0, pc_systems[pctype].lambda0, x, y, gamma, pctype);
	default:
		return 1; 
	}
}

EXTERNC int WINAPI project_xy_to_philambda(double x, double y, double *phi, double *lambda, double *gamma, PCTYPE pctype)
{
	switch(pc_systems[pctype].prjtype){
	case PT_UTM:
		return utm_project_xy_to_philambda(x, y, phi, lambda, gamma, pctype); 
	case PT_HATT:
		return hatt_project_xy_to_philambda(x, y, pc_systems[pctype].phi0, pc_systems[pctype].lambda0, phi, lambda, gamma, pctype);
	default:
		return 1; 
	}
}

EXTERNC int WINAPI gr87_philambda_to_xy(double phi, double lambda, double *x, double *y, double *gamma)
{
  return project_philambda_to_xy(phi, lambda, x, y, gamma, PC_GR87);
}

EXTERNC int WINAPI gr87_xy_to_philambda(double x, double y,	double *phi, double *lambda, double *gamma)
{
  return project_xy_to_philambda(x, y, phi, lambda, gamma, PC_GR87); 
}

EXTERNC int WINAPI displace_geodetic_system(double phi, double lambda, double *resulting_phi, double *resulting_lambda, GSTYPE source, GSTYPE dest)
{
	double x, y, z, x2, y2, z2;

	philambda_to_xyz(phi, lambda, &x, &y, &z, source);
	displace_geocentric_system(x, y, z, &x2, &y2, &z2, source, dest);
	ellipsoid_xyz_to_philambda(x2, y2, z2, resulting_phi, resulting_lambda, dest);
	return errno;
}

EXTERNC int WINAPI wgs84_philambda_to_gr87_xy(double phi, double lambda, double *x, double *y, double *gamma)
{
    double phi2, lambda2;

	displace_geodetic_system(phi, lambda, &phi2, &lambda2, GS_WGS84, GS_GR87);
	gr87_philambda_to_xy(phi2, lambda2, x, y, gamma);
	return errno;
}

EXTERNC int WINAPI wgs84_philambda_to_xy(double phi, double lambda, double *x, double *y, double *gamma, PCTYPE pctype)
{
    double phi2, lambda2;

	displace_geodetic_system(phi, lambda, &phi2, &lambda2, GS_WGS84, pc_systems[pctype].gstype);
	project_philambda_to_xy(phi2, lambda2, x, y, gamma, pctype);
	return errno;
}

EXTERNC int WINAPI gr87_xy_to_wgs84_philambda(double x, double y, double *phi, double *lambda, double *gamma)
{
	double phi2, lambda2;

	gr87_xy_to_philambda(x, y, &phi2, &lambda2, gamma);
	displace_geodetic_system(phi2, lambda2, phi, lambda, GS_GR87, GS_WGS84);
	return errno;
}

EXTERNC int WINAPI xy_to_wgs84_philambda(double x, double y, double *phi, double *lambda, double *gamma, PCTYPE pctype)
{
	double phi2, lambda2;

	project_xy_to_philambda(x, y, &phi2, &lambda2, gamma, pctype);
	displace_geodetic_system(phi2, lambda2, phi, lambda, pc_systems[pctype].gstype, GS_WGS84);
	return errno;
}

EXTERNC int WINAPI gr87_philambda_to_wgs84_philambda(double phi, double lambda, double *resulting_phi, double *resulting_lambda)
{
	displace_geodetic_system(phi, lambda, resulting_phi, resulting_lambda, GS_GR87, GS_WGS84); 
	return errno;
}

EXTERNC int WINAPI wgs84_philambda_to_gr87_philambda(double phi, double lambda, double *resulting_phi, double *resulting_lambda)
{
	displace_geodetic_system(phi, lambda, resulting_phi, resulting_lambda, GS_WGS84, GS_GR87); 
	return errno;
}

EXTERNC int WINAPI convert_xy(double x, double y, double *x2, double *y2, double *gamma, PCTYPE source, PCTYPE dest)
{
    double phi, lambda, phi2, lambda2;
	
	project_xy_to_philambda(x, y, &phi, &lambda, gamma, source);
	displace_geodetic_system(phi, lambda, &phi2, &lambda2, pc_systems[source].gstype, pc_systems[dest].gstype);
	project_philambda_to_xy(phi2, lambda2, x2, y2, gamma, dest);
	return errno;
}

EXTERNC int WINAPI convert_hatt_xy_to_xy(double x, double y, double phi0, double lambda0, double *x2, double *y2, double *gamma, PCTYPE pctype)
{
    double phi, lambda, phi2, lambda2;

	hatt_project_xy_to_philambda(x, y, phi0, lambda0, &phi, &lambda, gamma, PC_GR_HATT_ATHINA_CHALKIS); 
	displace_geodetic_system(phi, lambda, &phi2, &lambda2, GS_GR_BESSEL, pc_systems[pctype].gstype);
	project_philambda_to_xy(phi2, lambda2, x2, y2, gamma, pctype);
	return errno;
}

EXTERNC int WINAPI convert_xy_to_hatt_xy(double x, double y, double phi0, double lambda0, double *x2, double *y2, double *gamma, PCTYPE pctype)
{
    double phi, lambda, phi2, lambda2;

	project_xy_to_philambda(x, y, &phi, &lambda, gamma, pctype);
	displace_geodetic_system(phi, lambda, &phi2, &lambda2, pc_systems[pctype].gstype, GS_GR_BESSEL);
	hatt_project_philambda_to_xy(phi2, lambda2, phi0, lambda0, x2, y2, gamma, PC_GR_HATT_ATHINA_CHALKIS);
	return errno;
}

EXTERNC int WINAPI hatt_xy_to_wgs84_philambda(double x, double y, double phi0, double lambda0, double *phi, double *lambda, double *gamma, PCTYPE pctype)
{
	double phi2, lambda2;

	hatt_project_xy_to_philambda(x, y, phi0, lambda0, &phi2, &lambda2, gamma, pctype); 
	displace_geodetic_system(phi2, lambda2, phi, lambda, pc_systems[pctype].gstype, GS_WGS84);	
	return errno;
}

EXTERNC int WINAPI wgs84_philambda_to_hatt_xy(double phi, double lambda, double phi0, double lambda0, double *x, double *y, double *gamma, PCTYPE pctype)
{
	double phi2, lambda2;

	displace_geodetic_system(phi, lambda, &phi2, &lambda2, GS_WGS84, pc_systems[pctype].gstype);
	hatt_project_philambda_to_xy(phi2, lambda2, phi0, lambda0, x, y, gamma, pctype);
	return errno;
}
