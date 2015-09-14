/*******************************************************************************/
/* UTM - Ellipsoid Coordinates transforms                                      */
/* (c) 2006 by Stefanos Kozanis, N.T.U.A.                                      */
/* Distributed freely as a Public Domain software                              */
/*                                                                             */
/*******************************************************************************/

/* icoordstrans.h: Exported library functions
*/

#ifndef __EXPFUNCS_H__

#define __EXPFUNCS_H__

#include "main_types.h"

#ifdef _WINDOWS
	#define EXTERNC  extern "C"
	#define DLLAPI   __declspec(dllexport) //not needed since I use .def file
	#define WINAPI   __stdcall //__cdecl 
#else
	#define EXTERNC	extern
	#define DLLAPI
	#define WINAPI
#endif

/* Convert phi, lambda -> x,y on the Greek Reference System 1987. Returns by
   refence as well as the meridian convergence (gamma angle). Returns an
   error integer number. This Function is obsolete, use project_philambda_to_xy
   instead.
*/
EXTERNC int WINAPI gr87_philambda_to_xy(double, double, double*, double*, double* );

/* Convert x,y -> phi, lambda on the Greek Reference System 1987. Returns by
   refence as well as the meridian convergence (gamma angle). Returns an
   error integer number. This Function is obsolete, use project_xy_to_philambda
   instead.
*/
EXTERNC int WINAPI gr87_xy_to_philambda(double, double, double*, double*, double* );

/* Transforms the geographical coordinates phi, lambda between two datums, e.g.
   WGS84 -> ED50.
*/
EXTERNC int WINAPI displace_geodetic_system(double, double, double*, double*, GSTYPE, GSTYPE );

/* Convert WGS84 phi, lambda -> x,y on the Greek Reference System 1987. Returns by
   refence as well as the meridian convergence (gamma angle). Returns an
   error integer number. This Function is obsolete, use project_philambda_to_xy
   instead.
*/
EXTERNC int WINAPI wgs84_philambda_to_gr87_xy(double, double, double*, double*, double* );

/* Convert GR87 x,y -> WGS84 phi, lambda . Returns by
   refence as well as the meridian convergence (gamma angle). Returns an
   error integer number. This Function is obsolete, use project_xy_to_philambda
   instead.
*/
EXTERNC int WINAPI gr87_xy_to_wgs84_philambda(double, double, double* , double*, double*);

/* Transforms the geographical coordinates phi, lambda between GR87 and WGS84.
   This function is obsolete, use displace_geodetic_system instead.
*/
EXTERNC int WINAPI gr87_philambda_to_wgs84_philambda(double, double, double*, double*);

/* Transforms the geographical coordinates phi, lambda between WGS84 and GR87.
   This function is obsolete, use displace_geodetic_system instead.
*/
EXTERNC int WINAPI wgs84_philambda_to_gr87_philambda(double, double, double*, double*);

/* Projects ellispoidal coordinates (phi, lambda) to plane coordinate system (x, y)
   on the plane coordinate system pctype. phi, lambda datum is based on the pctype.
*/
EXTERNC int WINAPI project_philambda_to_xy(double, double, double* , double* , double* , PCTYPE);

/* Projects plane coordinates (x, y) to ellispoidal coordinates (phi, lambda)
   on the plane coordinate system pctype. phi, lambda datum is based on the pctype.
*/
EXTERNC int WINAPI project_xy_to_philambda(double, double, double*, double*, double*, PCTYPE);

/* Projects plane coordinates (x, y) to geocentric WGS84 ellispoidal coordinates (phi, lambda)
   on the plane coordinate system pctype.
*/
EXTERNC int WINAPI xy_to_wgs84_philambda(double , double , double*, double *, double *, PCTYPE);

/* Projects geocentric WGS84 ellispoidal coordinates (phi, lambda) to plane coordinate
system (x, y) on the plane coordinate system pctype.
*/
EXTERNC int WINAPI wgs84_philambda_to_xy(double , double , double*, double *, double *, PCTYPE);

/* Convert phi, lambda -> x,y on the Greek Hatt projection. phi0, lambda0 are the
   centre of the projection.
*/
EXTERNC int WINAPI hatt_project_philambda_to_xy(double , double , double , double , double *, double *, double *, PCTYPE);

/* Convert x,y -> phi, lambda on the Greek Hatt projection. phi0, lambda0 are the
   centre of the projection.
*/
EXTERNC int WINAPI hatt_project_xy_to_philambda(double , double , double , double , double* , double* , double* , PCTYPE);

/* Converts plane coordinates between two plane coordinate systems (source and dest).
*/
EXTERNC int WINAPI convert_xy(double, double, double*, double*, double*, PCTYPE, PCTYPE);

/* Converts plane coordinates between two plane coordinate systems (source and dest).
*/
EXTERNC int WINAPI convert_hatt_xy_to_xy(double, double, double, double, double*, double*, double*, PCTYPE);

/* Converts x,y from any system (pctype) to x,y of Greek Hatt system.
*/
EXTERNC int WINAPI convert_xy_to_hatt_xy(double , double , double , double , double*, double*, double*, PCTYPE);

/* Converts x,y from Greek Hatt system to any system (pctype) x,y 
*/
EXTERNC int WINAPI hatt_xy_to_wgs84_philambda(double, double, double, double, double*, double*, double*, PCTYPE);

/* Convert WGS84 phi, lambda -> x,y on Greek Hatt. Returns by
   refence as well as the meridian convergence (gamma angle).
*/
EXTERNC int WINAPI wgs84_philambda_to_hatt_xy(double, double, double, double, double*, double*, double*, PCTYPE);

/* UTM conversion phi, lambda -> x, y
*/
EXTERNC int WINAPI utm_project_philambda_to_xy(double , double , double* , double* , double* , PCTYPE );

/* UTM conversion x, y -> phi, lambda
*/
EXTERNC int WINAPI utm_project_xy_to_philambda(double , double , double* , double* , double* , PCTYPE );

#endif
