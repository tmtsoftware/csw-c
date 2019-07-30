//
// Created by abrighto on 7/28/19.
//

#ifndef CSW_C_COORDS_H
#define CSW_C_COORDS_H

#include "Event.h"

// A tag is a label to indicate the use of the coordinate
typedef struct {
    char *name;
} CswTag;

// A wrapper for Angle values (See the csw.params.core.models.Angle class).
// Normally Angle would be stored in double as radians, but this introduces rounding errors.
// This struct stores the value in microarc seconds to prevent rounding errors.
typedef struct {
    int uas;
} CswAngle;

typedef enum {
    ICRS,
    FK5
} CswEqFrame;

typedef struct {
    float pmx;
    float pmy;
} CswProperMotion;

typedef enum {
    Mercury,
    Venus,
    Moon,
    Mars,
    Jupiter,
    Saturn,
    Neptune,
    Uranus,
    Pluto
} CswSolarSystemObject;

// A subset of KeyType used for coordinate types
typedef enum {
    EqCoordKeyType = EqCoordKey,
    SolarSystemCoordKeyType = SolarSystemCoordKey,
    MinorPlanetCoordKeyType = MinorPlanetCoordKey,
    CometCoordKeyType = CometCoordKey,
    AltAzCoordKeyType = AltAzCoordKey,
} CswCoordKeyType;

// Common base type of coordinate types (Used to figure out which type of coordinate it is when key is CoordKey)
typedef struct {
    CswCoordKeyType keyType; // needed to determine "virtual" type of coord
    CswTag tag;
} CswCoord;

// Represents equatorial coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CswCoordKeyType keyType;
    CswTag tag;
    CswAngle dec;
    CswEqFrame frame;
    char *catalogName;
    CswProperMotion pm;
} CswEqCoord;

// Represents Solar System Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CswCoordKeyType keyType;
    CswTag tag;
    CswSolarSystemObject body;
} CswSolarSystemCoord;


// Represents Minor Planet Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CswCoordKeyType keyType;
    CswTag tag;
    float epoch;
    CswAngle inclination;
    CswAngle longAscendingNode;
    CswAngle argOfPerihelion;
    float meanDistance;  // AU
    float eccentricity;
    CswAngle meanAnomaly;
} CswMinorPlanetCoord;

// Represents Comet Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CswCoordKeyType keyType;
    CswTag tag;
    float epochOfPerihelion;
    CswAngle inclination;
    CswAngle longAscendingNode;
    CswAngle argOfPerihelion;
    float perihelionDistance;  // AU
    float eccentricity;
} CswCometCoord;

// Represents Alt-Az Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CswCoordKeyType keyType;
    CswTag tag;
    CswAngle alt;
    CswAngle az;
} CswAltAzCoord;

#endif //CSW_C_COORDS_H
