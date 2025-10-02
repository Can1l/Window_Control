#include "aoicalc.h"
#include "commonlib.h"
#include <math.h> 

void degToCartesian(double azimuth, double elevation, double *coords) {
    double phi = deg2rad(azimuth);
    double eps = deg2rad(elevation);

    coords[0] = cos(eps) * cos(phi);
    coords[1] = cos(eps) * sin(phi);
    coords[2] = sin(eps);
}

void applyPan(double pan, double *coords) {
    double p = deg2rad(pan);
	double x = coords[0];
	double y = coords[1];

    coords[0] = y * sin(p) + x * cos(p);
    coords[1] = y * cos(p) - x * sin(p);
	//coords[2] = z;
}

void applyTilt(double tilt, double *coords) {    
    double t = deg2rad(tilt);
	double x = coords[0];
	double z = coords[2];

    coords[0] = x * cos(t) - z * sin(t);
    //coords[1] = y;
    coords[2] = x * sin(t) + z * cos(t);
}

void applyTiltCorrection(double tilt, double *coords) {
    if (tilt > TILT_MAX) {
        double rot = PI; // 180°
		double x = coords[0];
		double y = coords[1];
        coords[0] = y * sin(rot) + x * cos(rot);
        coords[1] = y * cos(rot) - x * sin(rot);
		//coords[2] = z;
	}
}

AOI cartesianToAngles(double *coords) {
	AOI _aoi;
    // Clip de z
    if (coords[2] > 1.0) coords[2] = 1.0;
    if (coords[2] < -1.0) coords[2] = -1.0;

    // Proyección a AOIL y AOIT
    if (coords[2] != 0) {
        _aoi.AOIl = rad2deg(atan(coords[1] / coords[2]));
        _aoi.AOIt = rad2deg(atan(coords[0] / coords[2]));
    } else {
        _aoi.AOIl = 0.0;
        _aoi.AOIt = 0.0;
    }

    return _aoi;
}

AOI ephToAOI(double azimuth, double elevation, double pan, double tilt){
    double coords[3] = {0,0,0};
    degToCartesian(azimuth, elevation, coords);
    applyPan(pan, coords);
    applyTilt(tilt, coords);
    applyTiltCorrection(tilt, coords);
    return cartesianToAngles(coords); 
}



