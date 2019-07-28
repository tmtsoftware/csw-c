//
// Created by abrighto on 7/26/19.
//

#ifndef CSW_C_PARAMETER_H
#define CSW_C_PARAMETER_H


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
} KeyType;

typedef struct {
    // An array of primitive values, or a nested array for array and matrix types or the csw "struct" type.
    void *values;

    // The number of values in the above array
    int numValues;
} ArrayValue;

// A Parameter (keys with values, units).
typedef struct {

    KeyType keyType;

    char *keyName;

    ArrayValue values;

    // See https://tmtsoftware.github.io/csw/0.7.0-RC1/messages/units.html for list of unit names.
    char *units;
} Parameter;


// A Struct (value when key is "StructKey").
typedef struct {
    // a list of Parameters that make up the Struct
    Parameter *paramSet;

    // The number of parameters in this Struct
    int numParams;
} Struct;


cbor_item_t *parameterAsMap(Parameter param);


#endif //CSW_C_PARAMETER_H
