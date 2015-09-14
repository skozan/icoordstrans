/*******************************************************************************/
/* UTM - Ellipsoid Coordinates transforms                                      */
/* (c) 2006 by Stefanos Kozanis, N.T.U.A.                                      */
/* Distributed freely as a Public Domain software                              */
/*                                                                             */
/*******************************************************************************/

/* corefuncs.h: Core mathematical functions header file
*/

#ifndef __COREFUNCS_H__

#define __COREFUNCS_H__

#include "main_types.h"

/* Convertion of geographical coordinates to a geocentric system */
extern void philambda_to_xyz(double , double , double* , double* , double* , GSTYPE );

/* Conversion of geocentric coordinates to spherical */
extern void sphere_xyz_to_philambda(double , double , double , double* , double* , double );

/* Conversion of geocentric coordinates to ellipsoid phi & lambda */
extern void ellipsoid_xyz_to_philambda(double , double , double , double* , double* , GSTYPE);

/* Calculate the meridian arc on an ellipsoid surface for a given phi */
extern double ellipsoid_arc(double, GSTYPE );

/* Calculate the main normal section radius of an ellipsoid at phi */
extern double ellipsoid_main_normal_section_radius(double, GSTYPE );

/* Internal function to make several iterrations for UTM projection */
extern double fit(double , PCTYPE );

/* Calculate the e2 of an ellipsoid */
extern double get_e2(GSTYPE );

/* Calculate the et2 of an ellipsoid */
extern double get_et2(GSTYPE );

/* Calculate the meridian radius ro of an ellipsoid */
extern double ellipsoid_meridian_radius(double , GSTYPE );

/* Helmert seven parameter 3D transform. Angles should be in radians with small values
   as the expressions sin(x)=tan(x)=x and cos(x)=1 are valid */
extern void helmert_transform(double , double , double , double* , double* , double* , GSTYPE , double );

/* Displace XYZ geocentric systems with Helmert 3D transform */
extern void displace_geocentric_system(double , double , double , double* , double* , double* , GSTYPE , GSTYPE );

#endif
