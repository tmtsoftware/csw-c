//
// Created by abrighto on 7/28/19.
//

#ifndef CSW_C_COORDS_H
#define CSW_C_COORDS_H

// A tag is a label to indicate the use of the coordinate
typedef struct {
    char *name;
} Tag;

// A wrapper for Angle values (See the csw.params.core.models.Angle class).
// Normally Angle would be stored in double as radians, but this introduces rounding errors.
// This struct stores the value in microarc seconds to prevent rounding errors.
typedef struct {
    int uas;
} CSwAngle;

typedef enum {
    ICRS,
    FK5
} EqFrame;

typedef struct {
    float pmx;
    float pmy;
} ProperMotion;

// Represents equatorial coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    Tag tag;
    CSwAngle dec;
    EqFrame frame;
    char *catalogName;
    ProperMotion pm;
} EqCoord;

#endif //CSW_C_COORDS_H
