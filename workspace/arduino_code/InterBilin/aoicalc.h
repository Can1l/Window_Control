#ifndef aoicalc_h
#define aoicalc_h

#ifdef __cplusplus
extern "C" {
#endif

#define TILT_MAX 45 // Angle in degrees 

typedef struct{
	double _AOI;
	double AOIl;
	double AOIt;
	double azimuth, phi;
	double elevation, eps;
	double pan, pan_rad;
	double tilt, tilt_rad;
	double x, y, z;
} AOI;



// sferical coordinates to cartesian coordinates
AOI degToCartesian(double azimuth, double elevation);
//clockwise rotation around the Z axis
AOI applyPan(double pan, double _x, double _y);  
double zClip(double _z);
// Tilt (y rotation)
AOI applyTilt(double tilt, double _x, double _z);

 // Tilt correction when tilt > max_tilt
AOI applyTiltCorrection(double _x, double _y) ;

// AOIl AOIt 
AOI cartesianToAngles(double _x, double _y, double _z);


AOI cartesianToNewEph(double _x, double _y, double _z);
/*
AOI newEphToAOI (struct Eph);
AOI ephToNewEPh(double azimuth, double elevation, double pan, double tilt);

AOI ephToToAOI(double azimuth, double elevation, double pan, double tilt);
AOI ephToAOI2(double azimuth, double elevation, double pan, double tilt);
*/
#ifdef __cplusplus
}
#endif

#endif
