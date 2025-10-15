#include "aoicalc.h"
#include "commonlib.h"
#include <math.h> 
#include <Arduino.h>


// sferical coordinates to cartesian coordinates
AOI degToCartesian(double azimuth, double elevation) {
    AOI result;
    result.phi = deg2rad(azimuth);
    result.eps = deg2rad(elevation);
    result.x = cos(result.eps) * cos(result.phi);
    result.y = cos(result.eps) * sin(result.phi);
    result.z = sin(result.eps);
    return result;
}

//clockwise rotation around the Z axis
AOI applyPan(double pan, double _x, double _y) {
    AOI result;

    result.pan_rad = deg2rad(pan);
    result.x = _y * sin(result.pan_rad) + _x * cos(result.pan_rad);
    result.y = _y * cos(result.pan_rad) - _x * sin(result.pan_rad);
	//coords[2] = z;
    return result;
}

//clockwise rotation around the Y axis
AOI applyTilt(double tilt, double _x, double _z) {    
    AOI result;
    result.tilt_rad = deg2rad(tilt);
    result.x = _x * cos(result.tilt_rad) - _z * sin(result.tilt_rad);
    result.z = _x * sin(result.tilt_rad) + _z * cos(result.tilt_rad);
    return result;
}

AOI applyTiltCorrection(double _x, double _y) {
    AOI result;
    double rot = PI; // 180°
    result.x = _y * sin(rot) + _x * cos(rot);
    result.y = _y * cos(rot) - _x * sin(rot);
    return result;
}
double zClip(double _z){
    // z clip 
    if (_z > 1.0) _z = 1.0;
    if (_z < -1.0) _z = -1.0;
    return _z;
}

AOI cartesianToNewEph(double _x, double _y, double _z) {
    AOI result;

    // z clip
    result.x = _x;
	result.y = _y;
    result.z = zClip(_z);

    // AOIl AOIt proyections
    if (_z != 0) {
        result.elevation = rad2deg(asin(result.z));
        result.azimuth = rad2deg(atan2(_y, _x));
    } else {
        result.elevation = 0.0;
        result.azimuth = 0.0;
    }

    return result;
}
AOI cartesianToAngles(double _x, double _y, double _z) {
    AOI res;
    // z clip
	res.x = _x;
	res.y = _y;
    res.z = zClip(_z);
    
    // AOIL AOIT proyections
    if (_z != 0) {
        res._AOI = rad2deg(acos(res.z));
        res.AOIl = rad2deg(atan2(_y, _z));
        res.AOIt = rad2deg(atan2(_x, _z));
    } else {
        res._AOI = 0.0;
        res.AOIl = 0.0;
        res.AOIt = 0.0;
    }
    return res;
}
/*
AOI ephToNewEph(double azimuth, double elevation, double pan, double tilt){
    double coords[3] = {0,0,0};
    Eph new_eph;
    degToCartesian(azimuth, elevation, coords);
    applyPan(pan, coords);
    applyTilt(tilt, coords);
    applyTiltCorrection(tilt, coords);   
    return new_eph = cartesianToNewEph(coords); // H, 𝛿
}
AOI newEphToAOI (struct Eph) {
    degToCartesian(Eph.azimuth, Eph.elevation, coords);
    return cartesianToAngles(coords);
}
AOI ephToToAOI(double azimuth, double elevation, double pan, double tilt){
    double coords[3] = {0,0,0};
    Eph new_eph;
    degToCartesian(azimuth, elevation, coords);
    applyPan(pan, coords);
    applyTilt(tilt, coords);
    applyTiltCorrection(tilt, coords);   
    new_eph = cartesianToNewEph(coords); // H, 𝛿
    degToCartesian(Eph.azimuth, Eph.elevation, coords);
    return cartesianToAngles(coords);
}

AOI ephToAOI2(double azimuth, double elevation, double pan, double tilt){
    double coords[3] = {0,0,0};
    degToCartesian(azimuth, elevation, coords);
    applyPan(pan, coords);
    applyTilt(tilt, coords);
    applyTiltCorrection(tilt, coords);   
    return cartesianToAngles(coords);
}*/


