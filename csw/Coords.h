//
// Created by abrighto on 7/28/19.
//

#ifndef CSW_C_COORDS_H
#define CSW_C_COORDS_H

#include "Event.h"

// A tag is a label to indicate the use of the coordinate
typedef struct {
    char *name;
} Tag;

// A wrapper for Angle values (See the csw.params.core.models.Angle class).
// Normally Angle would be stored in double as radians, but this introduces rounding errors.
// This struct stores the value in microarc seconds to prevent rounding errors.
typedef struct {
    int uas;
} CswAngle;

typedef enum {
    ICRS,
    FK5
} EqFrame;

typedef struct {
    float pmx;
    float pmy;
} ProperMotion;

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
} SolarSystemObject;

// A subset of KeyType used for coordinate types
typedef enum {
    EqCoordKeyType = EqCoordKey,
    SolarSystemCoordKeyType = SolarSystemCoordKey,
    MinorPlanetCoordKeyType = MinorPlanetCoordKey,
    CometCoordKeyType = CometCoordKey,
    AltAzCoordKeyType = AltAzCoordKey,
} CoordKeyType;

// Common base type of coordinate types (Used to figure out which type of coordinate it is when key is CoordKey)
typedef struct {
    CoordKeyType keyType; // needed to determine "virtual" type of coord
    Tag tag;
} Coord;

// Represents equatorial coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CoordKeyType keyType;
    Tag tag;
    CswAngle dec;
    EqFrame frame;
    char *catalogName;
    ProperMotion pm;
} EqCoord;

// Represents Solar System Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CoordKeyType keyType;
    Tag tag;
    SolarSystemObject body;
} SolarSystemCoord;


//epoch: float  # TT as a Modified Julian Date
//inclination: Angle
//        longAscendingNode: Angle
//        argOfPerihelion: Angle
//        meanDistance: float  # AU
//        eccentricity: float
//        meanAnomaly: Angle


// Represents Minor Planet Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CoordKeyType keyType;
    Tag tag;
    float epoch;
    CswAngle inclination;
    CswAngle longAscendingNode;
    CswAngle argOfPerihelion;
    float meanDistance;  // AU
    float eccentricity;
    CswAngle meanAnomaly;
} MinorPlanetCoord;

// Represents Comet Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CoordKeyType keyType;
    Tag tag;
    float epochOfPerihelion;
    CswAngle inclination;
    CswAngle longAscendingNode;
    CswAngle argOfPerihelion;
    float perihelionDistance;  // AU
    float eccentricity;
} CometCoord;

// Represents Alt-Az Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CoordKeyType keyType;
    Tag tag;
    CswAngle alt;
    CswAngle az;
} AltAzCoord;

#endif //CSW_C_COORDS_H
