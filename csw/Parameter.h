//
// Created by abrighto on 7/26/19.
//

#ifndef CSW_C_PARAMETER_H
#define CSW_C_PARAMETER_H

#include <cbor.h>

typedef enum {
    ChoiceKey,
    StringKey,
    StructKey,
    UTCTimeKey,
    TAITimeKey,
    RaDecKey,
    EqCoordKey,
    SolarSystemCoordKey,
    MinorPlanetCoordKey,
    CometCoordKey,
    AltAzCoordKey,
    CoordKey,
    BooleanKey,
    CharKey,
    ByteKey,
    ShortKey,
    LongKey,
    IntKey,
    FloatKey,
    DoubleKey,
    ByteArrayKey,
    ShortArrayKey,
    LongArrayKey,
    IntArrayKey,
    FloatArrayKey,
    DoubleArrayKey,
    ByteMatrixKey,
    ShortMatrixKey,
    LongMatrixKey,
    IntMatrixKey,
    FloatMatrixKey,
    DoubleMatrixKey
} CswKeyType;

typedef struct {
    // An array of primitive values, or a nested array for array and matrix types or the csw "struct" type.
    void *values;

    // The number of values in the above array
    int numValues;
} CswArrayValue;

// A Parameter (keys with values, units).
typedef struct {

    CswKeyType keyType;

    char *keyName;

    CswArrayValue values;

    // See https://tmtsoftware.github.io/csw/0.7.0-RC1/messages/units.html for list of unit names.
    char *units;
} CswParameter;


// A Struct (value when key is "StructKey").
typedef struct {
    // a list of Parameters that make up the Struct
    CswParameter *paramSet;

    // The number of parameters in this Struct
    int numParams;
} CswStruct;


cbor_item_t *_cswParameterAsMap(CswParameter param);
struct cbor_pair _cswMakeStringPair(const char *key, const char *value);
struct cbor_pair _cswMakeItemPair(const char *key, cbor_item_t *value);
struct cbor_pair _cswMakeParamSetItemPair(const CswParameter* paramSet, int numParams);


#endif //CSW_C_PARAMETER_H
