/*******************************************************************************/
/* UTM - Ellipsoid Coordinates transforms                                      */
/* (c) 2006 by Stefanos Kozanis, N.T.U.A.                                      */
/* Distributed freely as a Public Domain software                              */
/*                                                                             */
/*******************************************************************************/

/* main_types.h: Common storage types and constants - header file
*/

#ifndef __MAIN_TYPES_H__

#define __MAIN_TYPES_H__

#define PI				   3.1415926535897932384626433832795

/***********************************************************/
/* Ellipsoids geometry (Alpha: Big semi-axis, F_INV = 1/f) */
/***********************************************************/

/* GRS80 Ellipsoid */
#define GE_GRS80_Alpha		6378137.000
#define GE_GRS80_F_INV		298.257222101
/* WGS84 Ellipsoid */
#define GE_WGS84_Alpha		6378137.000
#define GE_WGS84_F_INV		298.257223563
/* Hayford International Ellipsoid */
#define GE_HAYFORD_Alpha	6378388.000
#define GE_HAYFORD_F_INV	297.000
/* Bessel Ellipsoid */
#define GE_BESSEL_Alpha		6377397.155
#define GE_BESSEL_F_INV		299.1528128


/*********************************************************************/
/* Datums: ellipsoids displacements, rotations and scale change      */
/* from the geocentric WGS84 ellipsoid (add these values to local    */
/* systems to obtain WGS84).                                         */
/*********************************************************************/

#define GS_WGS84_DX					0.00
#define GS_WGS84_DY					0.00
#define GS_WGS84_DZ					0.00
#define GS_WGS84_RX					0.00
#define GS_WGS84_RY					0.00
#define GS_WGS84_RZ					0.00
#define GS_WGS84_DS					0.00
#define GS_GR87_DX				 -199.72
#define GS_GR87_DY				   74.03
#define GS_GR87_DZ				  246.02
#define GS_GR87_RX				    0.00
#define GS_GR87_RY				    0.00
#define GS_GR87_RZ				    0.00
#define GS_GR87_DS				    0.00
#define GS_ED50_CYPRUS_DX		 -104.00
#define GS_ED50_CYPRUS_DY		 -101.00
#define GS_ED50_CYPRUS_DZ		 -140.00
#define GS_ED50_CYPRUS_RX		    0.00
#define GS_ED50_CYPRUS_RY		    0.00
#define GS_ED50_CYPRUS_RZ		    0.00
#define GS_ED50_CYPRUS_DS		    0.00
#define GS_ED50_GREECE_DX		  -83.80
#define GS_ED50_GREECE_DY		  -96.30
#define GS_ED50_GREECE_DZ		 -115.70
#define GS_ED50_GREECE_RX		    0.00
#define GS_ED50_GREECE_RY		    0.00
#define GS_ED50_GREECE_RZ		    0.00
#define GS_ED50_GREECE_DS		    0.00
#define GS_ED50_MEANEUROPE_DX	  -87.00
#define GS_ED50_MEANEUROPE_DY	  -98.00
#define GS_ED50_MEANEUROPE_DZ	 -121.00
#define GS_ED50_MEANEUROPE_RX	    0.00
#define GS_ED50_MEANEUROPE_RY	    0.00
#define GS_ED50_MEANEUROPE_RZ	    0.00
#define GS_ED50_MEANEUROPE_DS	    0.00
#define GS_GR_BESSEL_DX			  456.39
#define GS_GR_BESSEL_DY			  372.62
#define GS_GR_BESSEL_DZ			  496.82
#define GS_GR_BESSEL_RX			  -12.664e-6
#define GS_GR_BESSEL_RY		       -5.620e-6
#define GS_GR_BESSEL_RZ	   	      -10.854e-6
#define GS_GR_BESSEL_DS			   15.9e-6

/**************************************************************/
/* Projected (plane coordinates) reference systems parameters */
/* (constants)                                                */
/**************************************************************/

#define PC_GR87_PHI0		0.00
#define PC_GR87_LAMBDA0		(24.00*PI/180.00)
#define PC_GR87_XOFFSET		500000
#define PC_GR87_YOFFSET		0.00
#define PC_GR87_KAPPA		0.9996
#define PC_UTM_PHI0			0.00
#define PC_UTM_LAMBDA0		(-177.00*PI/180.00)
#define PC_UTM_XOFFSET		500000.00
#define PC_UTM_YOFFSET		0.00
#define PC_UTM_KAPPA		0.9996
#define PC_ED50_PHI0		0.00
#define PC_ED50_LAMBDA0		(-3.00*PI/180.00)
#define PC_ED50_XOFFSET		500000.00
#define PC_ED50_YOFFSET		0.00
#define PC_ED50_KAPPA		0.9996
#define PC_GR_HATT_PHI0			(37.97225*PI/180.00)
#define PC_GR_HATT_LAMBDA0		(23.7163375*PI/180.00)
#define PC_GR_HATT_XOFFSET		0.00
#define PC_GR_HATT_YOFFSET		0.00
#define PC_GR_HATT_KAPPA		1.000
#define PC_GR_UTM3_PHI0			(34.0000000*PI/180.00)
#define PC_GR_UTM3_LAMBDA0		(23.7163375*PI/180.00)
#define PC_GR_UTM3_XOFFSET		200000.00
#define PC_GR_UTM3_YOFFSET		-3762911.963
#define PC_GR_UTM3_KAPPA		0.9999

/* Ellipsoid geometry structure */
typedef struct ell_geometry ELLIPSOID_GEOMETRY;

/* Geodetic system structure */
typedef struct geodetic_system GSYSTEM;

/* Plane coordinate system structure */
typedef struct plane_coords_system PCSYSTEM;

/* Geodetic systems (Datums) enum type */
typedef enum gstype {
	GS_GR87 = 0,
	GS_WGS84 = 1,
	GS_ED50_CYPRUS = 2,
	GS_ED50_GREECE = 3,
	GS_ED50_MEANEUROPE = 4,
	GS_GR_BESSEL = 5
} GSTYPE;

/* Ellipsoids enum type*/
typedef enum gellipsoid {
	GE_GRS80 = 0,
	GE_WGS84 = 1,
	GE_HAYFORD = 2,
	GE_BESSEL = 3
} GELLIPSOID;

/* Plane coordinate (reference) Systems enum type*/
typedef enum pctype {
	PC_GR87 = 0,
	PC_UTM_ZONE29 = 1,
	PC_UTM_ZONE30 = 2,
	PC_UTM_ZONE31 = 3,
	PC_UTM_ZONE32 = 4,
	PC_UTM_ZONE33 = 5,
	PC_UTM_ZONE34 = 6,
	PC_UTM_ZONE35 = 7,
	PC_UTM_ZONE36 = 8,	
	PC_UTM_ZONE37 = 9,
	PC_ED50_CYPRUS_ZONE6 = 10,
	PC_ED50_GREECE_ZONE4 = 11,
	PC_ED50_GREECE_ZONE5 = 12,
	PC_ED50_MEANEUROPE_ZONE0 = 13,
	PC_ED50_MEANEUROPE_ZONE1 = 14,
	PC_ED50_MEANEUROPE_ZONE2 = 15,
	PC_ED50_MEANEUROPE_ZONE3 = 16,
	PC_ED50_MEANEUROPE_ZONE4 = 17,
	PC_ED50_MEANEUROPE_ZONE5 = 18,
	PC_ED50_MEANEUROPE_ZONE6 = 19,
	PC_GR_HATT_ATHINA_CHALKIS = 20,
	PC_GR_HATT_ATHINA_LAVRION = 21,
	PC_GR_HATT_AEGINA = 22,
	PC_GR_HATT_NEA_PSARA = 23,
	PC_GR_HATT_THESSALONIKI = 24,
	PC_GR_HATT_GIANNITSA = 25,
	PC_GR_UTM3_WEST = 26,
	PC_GR_UTM3_CENTRAL = 27,
	PC_GR_UTM3_EAST = 28
} PCTYPE;

/* Map projections enum type*/
typedef enum projection_type {
/* Universal transverse mercatoric */	
	PT_UTM = 0,
/* Hatt projection */
	PT_HATT =1
} PRJTYPE;

/* Array constants with ellipsoid structures */
extern ELLIPSOID_GEOMETRY ellipsoids[];

/* Array constants with datums structures */
extern GSYSTEM geodetic_systems[];

/* Array constants with plane coordinate systems structures */
extern PCSYSTEM pc_systems[];

/* Ellipsoid geometry structure */
typedef struct ell_geometry {
/* Alpha - big semi axis */
	double Big_Semiaxis;
/* Inverted F. F=(a-b)/a */
	double InvF;
} ELLIPSOID_GEOMETRY;

/* Geodetic system structure */
typedef struct geodetic_system {
/* Ellipsoid used */
	GELLIPSOID ellipsoid;
/* Displacements: X(geocentric) = X(datum)+DX */
	double DX;
	double DY;
	double DZ;
/* Rotations in radians*/
	double RX;
	double RY;
	double RZ;
/* Scale difference in numeric value (e.g. 1e-6, not 1 ppm)*/
	double DS;
} GSYSTEM; 

/* Plane coordinate system structure */
typedef struct plane_coords_system {
/* Datum */
	GSTYPE gstype;
/* Projection */
	PRJTYPE prjtype;
/* Geographical offset */
	double phi0;
	double lambda0;
/* X,Y offset */
	double xoffset;
	double yoffset;
/* Initial scale at phi0 */
	double kappa0;
} PCSYSTEM;

#endif
