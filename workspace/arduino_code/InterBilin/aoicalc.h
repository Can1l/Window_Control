#ifndef aoicalc_h
#define aoicalc_h

#ifdef __cplusplus
extern "C" {
#endif

#define TILT_MAX 45 // Angle in grades 

typedef struct{
double AOIl;
double AOIt;
} AOI;

// Pan (z rotation)
void degToCartesian(double azimuth, double elevation, double *coords);

void applyPan(double pan, double *coords);  

// Tilt (y rotation)
void applyTilt(double tilt, double *coords);

 // Tilt correction when tilt > max_tilt
void applyTiltCorrection(double tilt, double *coords);

// AOIl AOIt 
AOI cartesianToAngles(double *coords);


AOI ephToAOI(double azimuth, double elevation, double pan, double tilt);

#ifdef __cplusplus
}
#endif

#endif
