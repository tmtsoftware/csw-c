//
// Created by abrighto on 7/26/19.
//

#include <string.h>
#include <cbor.h>
#include "csw.h"
#include "cswImpl.h"

/**
 * Constructor for CswParameter.
 */
CswParameter cswMakeParameter(const char *keyName, CswKeyType keyType, CswArrayValue values, const char *units) {
    CswParameter p = {.keyType = keyType, .keyName = keyName, .values = values, .units = units};
    return p;
}

void cswFreeParameter(CswParameter param) {
    // XXX TODO
}

// --- KeyTypes ---

static const char *_keyTypeNames[] = {
        "ChoiceKey",
        "StringKey",
        "StructKey",
        "UTCTimeKey",
        "TAITimeKey",
        "RaDecKey",
        "EqCoordKey",
        "SolarSystemCoordKey",
        "MinorPlanetCoordKey",
        "CometCoordKey",
        "AltAzCoordKey",
        "CoordKey",
        "BooleanKey",
        "CharKey",
        "ByteKey",
        "ShortKey",
        "LongKey",
        "IntKey",
        "FloatKey",
        "DoubleKey",
        "ByteArrayKey",
        "ShortArrayKey",
        "LongArrayKey",
        "IntArrayKey",
        "FloatArrayKey",
        "DoubleArrayKey",
        "ByteMatrixKey",
        "ShortMatrixKey",
        "LongMatrixKey",
        "IntMatrixKey",
        "FloatMatrixKey",
        "DoubleMatrixKey"
};

static const size_t numKeyTypes = sizeof(_keyTypeNames) / sizeof(char *);

// Gets the name for the given key
static const char *_keyTypeName(CswKeyType keyType) {
    return _keyTypeNames[keyType];
}

// Gets the enum value for the given key type
static CswKeyType _keyTypeValue(const char *keyTypeName) {
    for (int i = 0; i < numKeyTypes; i++) {
        if (strncmp(_keyTypeNames[i], keyTypeName, strlen(_keyTypeNames[i])) == 0) {
            return i;
        }
    }
    return -1;
}

// --- EqFrame ---

static const char *_eqFrameNames[] = {
        "ICRS",
        "FK5"
};

static const size_t numEqFrames = sizeof(_eqFrameNames) / sizeof(char *);

// Gets the name for the given EqFrame enum value
static const char *_eqFrameName(CswEqFrame eqFrame) {
    return _eqFrameNames[eqFrame];
}

// Gets the enum value for the given EQFrame name
static CswEqFrame _eqFrameValue(const char *eqFrameName) {
    for (int i = 0; i < numEqFrames; i++) {
        if (strncmp(_eqFrameNames[i], eqFrameName, strlen(_eqFrameNames[i])) == 0) {
            return i;
        }
    }
    return -1;
}

// --- Solar System Object ---

static const char *_solarSystemObjectNames[] = {
        "Mercury",
        "Venus",
        "Moon",
        "Mars",
        "Jupiter",
        "Saturn",
        "Neptune",
        "Uranus",
        "Pluto"
};

static const size_t numSolarSystemObjects = sizeof(_solarSystemObjectNames) / sizeof(char *);

// Gets the name for the given CswSolarSystemObject enum value
static const char *_solarSystemObjectName(CswSolarSystemObject solarSystemObject) {
    return _solarSystemObjectNames[solarSystemObject];
}

// Gets the enum value for the given EQFrame name
static CswSolarSystemObject _solarSystemObjectValue(const char *solarSystemObjectName) {
    for (int i = 0; i < numSolarSystemObjects; i++) {
        if (strncmp(_solarSystemObjectNames[i], solarSystemObjectName, strlen(_solarSystemObjectNames[i])) == 0) {
            return i;
        }
    }
    return -1;
}

// ---- To CBOR ---

static cbor_item_t *_makeStringItem(const char *value) {
    return cbor_move(cbor_build_string(value));
}

static cbor_item_t *_makeLongItem(long value) {
    if (value < 0)
        return cbor_move(cbor_build_negint64(-value - 1));
    else
        return cbor_move(cbor_build_uint64(value));
}

static cbor_item_t *_makeIntItem(int value) {
    if (value < 0)
        return cbor_move(cbor_build_negint32(-value - 1));
    else
        return cbor_move(cbor_build_uint32(value));
}

static cbor_item_t *_makeShortItem(short value) {
    if (value < 0)
        return cbor_move(cbor_build_negint16(-value - 1));
    else
        return cbor_move(cbor_build_uint16(value));
}

// XXX TODO: make UTF8 compatible?
static cbor_item_t *_makeCharItem(char value) {
    if (value < 0)
        return cbor_move(cbor_build_negint8(-value - 1));
    else
        return cbor_move(cbor_build_uint8(value));
}

static cbor_item_t *_makeFloatItem(float value) {
    return cbor_move(cbor_build_float4(value));
}

static cbor_item_t *_makeDoubleItem(double value) {
    return cbor_move(cbor_build_float8(value));
}

static cbor_item_t *_makeBooleanItem(bool value) {
    return cbor_move(cbor_build_bool(value));
}

static cbor_item_t *_arrayValueAsItem(CswKeyType keyType, const void *values, int index);

static cbor_item_t *_makeArrayItem(CswKeyType keyType, const CswArrayValue *values) {
    cbor_item_t *array = cbor_new_definite_array(values->numValues);
    for (int i = 0; i < values->numValues; i++) {
        cbor_array_push(array, _arrayValueAsItem(keyType, values->values, i));
    }
    return array;
}

struct cbor_pair _cswMakeStringPair(const char *key, const char *value) {
    return (struct cbor_pair) {
            .key = _makeStringItem(key),
            .value = _makeStringItem(value)
    };
}

static struct cbor_pair _makeIntPair(const char *key, int value) {
    return (struct cbor_pair) {
            .key = _makeStringItem(key),
            .value = _makeIntItem(value)
    };
}

static struct cbor_pair _makeFloatPair(const char *key, float value) {
    return (struct cbor_pair) {
            .key = _makeStringItem(key),
            .value = _makeFloatItem(value)
    };
}

struct cbor_pair _cswMakeItemPair(const char *key, cbor_item_t *value) {
    return (struct cbor_pair) {
            .key = _makeStringItem(key),
            .value = cbor_move(value)
    };
}

struct cbor_pair _cswMakeParamSetItemPair(const CswParameter* paramSet, int numParams) {
    cbor_item_t *array = cbor_new_definite_array(numParams);
    for (int i = 0; i < numParams; i++) {
        cbor_array_push(array, _cswParameterAsMap(paramSet[i]));
    }
    return _cswMakeItemPair("paramSet", array);
}

static cbor_item_t *_makeStructItem(CswParamSet value) {
    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _cswMakeParamSetItemPair(value.params, value.numParams));
    return map;
}

/**
 * Creates an array of array values for *ArrayKey types.
 *
 * @param values a two dim array of the form: int values3[2][4] = { {11,-22,33,-44}, {-55,66,-77,88} };
 * In this case there are two values, each of which is an array with 4 items.
 *
 * @param numArrays the number of array values
 *
 * @param numArrays the number of array values
 *
 * @param arrayValues an array of size numArrays used to hold the values. If null, space will be allocated with malloc,
 * in which case it should be freed by calling free(result.values)
 *
 * @return a CswArrayValue that can be used as the parameter value for *ArrayKey types
 */
CswArrayValue makeArrayValues(void** values, int numArrays, CswArrayValue arrayValues[numArrays], int arraySize) {
    if (arrayValues == NULL)
        arrayValues = malloc(numArrays * sizeof(CswArrayValue));
    for(int i = 0; i < numArrays; i++) {
        arrayValues[i].values = values + i;
        arrayValues[i].numValues = arraySize;
    }
    CswArrayValue result = {.values = arrayValues, .numValues = numArrays};
    return result;
}

// TODO: needs work...
//CswArrayValue makeMatrixValues(void*** values, int numMatrices, int numRows, int numCols) {
//    CswArrayValue* matrixValues = malloc(numMatrices * sizeof(CswArrayValue));
//    for(int i = 0; i < numMatrices; i++) {
//        matrixValues[i] = makeArrayValues(values[i], numRows, numCols);
//    }
//    CswArrayValue result = {.values = matrixValues, .numValues = numMatrices};
//    return result;
//}

static cbor_item_t *_makeEqCoordItem(CswEqCoord value) {
    cbor_item_t *valueMap = cbor_new_definite_map(6);
    cbor_map_add(valueMap, _cswMakeStringPair("tag", value.tag.name));
    cbor_map_add(valueMap, _makeIntPair("dec", value.dec.uas));
    cbor_map_add(valueMap, _cswMakeStringPair("frame", _eqFrameName(value.frame)));
    cbor_map_add(valueMap, _cswMakeStringPair("catalogName", value.catalogName));

    cbor_item_t *pmMap = cbor_new_definite_map(2);
    cbor_map_add(pmMap, _makeFloatPair("pmx", value.pm.pmx));
    cbor_map_add(pmMap, _makeFloatPair("pmy", value.pm.pmy));
    cbor_map_add(valueMap, _cswMakeItemPair("pm", pmMap));

    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _cswMakeItemPair("CswEqCoord", valueMap));
    return map;
}

static cbor_item_t *_makeSolarSystemCoordItem( CswSolarSystemCoord value) {
    cbor_item_t *valueMap = cbor_new_definite_map(2);
    cbor_map_add(valueMap, _cswMakeStringPair("tag", value.tag.name));
    cbor_map_add(valueMap, _cswMakeStringPair("frame", _solarSystemObjectName(value.body)));

    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _cswMakeItemPair("CswSolarSystemCoord", valueMap));
    return map;
}

static cbor_item_t *_makeMinorPlanetCoordItem( CswMinorPlanetCoord value) {
    cbor_item_t *valueMap = cbor_new_definite_map(8);
    cbor_map_add(valueMap, _cswMakeStringPair("tag", value.tag.name));
    cbor_map_add(valueMap, _makeFloatPair("epoch", value.epoch));
    cbor_map_add(valueMap, _makeIntPair("inclination", value.inclination.uas));
    cbor_map_add(valueMap, _makeIntPair("longAscendingNode", value.longAscendingNode.uas));
    cbor_map_add(valueMap, _makeIntPair("argOfPerihelion", value.argOfPerihelion.uas));
    cbor_map_add(valueMap, _makeFloatPair("meanDistance", value.meanDistance));
    cbor_map_add(valueMap, _makeFloatPair("eccentricity", value.eccentricity));
    cbor_map_add(valueMap, _makeIntPair("meanAnomaly", value.meanAnomaly.uas));

    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _cswMakeItemPair("CswMinorPlanetCoord", valueMap));
    return map;
}

static cbor_item_t *_makeCometCoordItem( CswCometCoord value) {
    cbor_item_t *valueMap = cbor_new_definite_map(7);
    cbor_map_add(valueMap, _cswMakeStringPair("tag", value.tag.name));
    cbor_map_add(valueMap, _makeFloatPair("epochOfPerihelion", value.epochOfPerihelion));
    cbor_map_add(valueMap, _makeIntPair("inclination", value.inclination.uas));
    cbor_map_add(valueMap, _makeIntPair("longAscendingNode", value.longAscendingNode.uas));
    cbor_map_add(valueMap, _makeIntPair("argOfPerihelion", value.argOfPerihelion.uas));
    cbor_map_add(valueMap, _makeFloatPair("perihelionDistance", value.perihelionDistance));
    cbor_map_add(valueMap, _makeFloatPair("eccentricity", value.eccentricity));

    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _cswMakeItemPair("CswCometCoord", valueMap));
    return map;
}

static cbor_item_t *_makeAltAzCoordItem(CswAltAzCoord value) {
    cbor_item_t *valueMap = cbor_new_definite_map(3);
    cbor_map_add(valueMap, _cswMakeStringPair("tag", value.tag.name));
    cbor_map_add(valueMap, _makeIntPair("alt", value.alt.uas));
    cbor_map_add(valueMap, _makeIntPair("az", value.az.uas));

    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _cswMakeItemPair("CswAltAzCoord", valueMap));
    return map;
}

static cbor_item_t *_makeCoordItem(CswCoord value) {
    switch (value.coordBase.keyType) {
        case EqCoordKeyType:
            return _makeEqCoordItem(value.eqCoord);
        case SolarSystemCoordKeyType:
            return _makeSolarSystemCoordItem(value.solarSystemCoord);
        case MinorPlanetCoordKeyType:
            return _makeMinorPlanetCoordItem(value.minorPlanetCoord);
        case CometCoordKeyType:
            return _makeCometCoordItem(value.cometCoord);
        case AltAzCoordKeyType:
            return _makeAltAzCoordItem(value.altAzCoord);
    }
}


// Returns a cbor item for the parameter value at the given index
static cbor_item_t *_arrayValueAsItem(CswKeyType keyType, const void *values, int index) {
    switch (keyType) {
        case ChoiceKey:
        case UTCTimeKey:
        case TAITimeKey:
        case StringKey:
            return _makeStringItem(values + index);
        case StructKey:
            return _makeStructItem(((CswParamSet*)values)[index]);
        case RaDecKey:
            return NULL; // TODO: FIXME
        case EqCoordKey:
            return _makeEqCoordItem(((CswEqCoord*)values)[index]);
        case SolarSystemCoordKey:
            return _makeSolarSystemCoordItem(((CswSolarSystemCoord*)values)[index]);
        case MinorPlanetCoordKey:
            return _makeMinorPlanetCoordItem(((CswMinorPlanetCoord*)values)[index]);
        case CometCoordKey:
            return _makeCometCoordItem(((CswCometCoord*)values)[index]);
        case AltAzCoordKey:
            return _makeAltAzCoordItem(((CswAltAzCoord*)values)[index]);
        case CoordKey:
            return _makeCoordItem(((CswCoord*)values)[index]);
        case BooleanKey:
            return _makeBooleanItem(((bool*)values)[index]);
        case CharKey:
            return _makeCharItem(((char*)values)[index]);
        case ByteKey:
            // XXX TODO FIXME: Need to use bytestring format here
            return _makeCharItem(((char*)values)[index]);
        case ShortKey:
            return _makeShortItem(((short*)values)[index]);
        case LongKey:
            return _makeLongItem(((long*)values)[index]);
        case IntKey:
            return _makeIntItem(((int*)values)[index]);
        case FloatKey:
            return _makeFloatItem(((float*)values)[index]);
        case DoubleKey:
            return _makeDoubleItem(((double*)values)[index]);
        case ByteArrayKey: {
            // TODO: Test this
//            return _makeArrayItem(ByteKey, (CswArrayValue *) values);
            CswArrayValue *ar = (CswArrayValue *) values;
            return cbor_build_bytestring((const unsigned char *) ar->values, ar->numValues);
        }
        case ShortArrayKey:
            return _makeArrayItem(ShortKey, ((CswArrayValue *) values) + index);
        case LongArrayKey:
            return _makeArrayItem(LongKey, ((CswArrayValue *) values) + index);
        case IntArrayKey:
            return _makeArrayItem(IntKey, ((CswArrayValue *) values) + index);
        case FloatArrayKey:
            return _makeArrayItem(FloatKey, ((CswArrayValue *) values) + index);
        case DoubleArrayKey:
            return _makeArrayItem(DoubleKey, ((CswArrayValue *) values) + index);
        case ByteMatrixKey:
            return _makeArrayItem(ByteArrayKey, ((CswArrayValue *) values) + index);
        case ShortMatrixKey:
            return _makeArrayItem(ShortArrayKey, ((CswArrayValue *) values) + index);
        case LongMatrixKey:
            return _makeArrayItem(LongArrayKey, ((CswArrayValue *) values) + index);
        case IntMatrixKey:
            return _makeArrayItem(IntArrayKey, ((CswArrayValue *) values) + index);
        case FloatMatrixKey:
            return _makeArrayItem(FloatArrayKey, ((CswArrayValue *) values) + index);
        case DoubleMatrixKey:
            return _makeArrayItem(DoubleArrayKey, ((CswArrayValue *) values) + index);
        default:
            return NULL;
    }
}

static cbor_item_t *_paramValuesAsMap(CswParameter param) {
    // Need to handle byte arrays differently (store as byte string)
    if (param.keyType == ByteKey) {
        return cbor_build_bytestring((const unsigned char *) param.values.values, param.values.numValues);
    } else {
        cbor_item_t *array = cbor_new_definite_array(param.values.numValues);
        for (int i = 0; i < param.values.numValues; i++) {
            cbor_array_push(array, _arrayValueAsItem(param.keyType, param.values.values, i));
        }
        return array;
    }
}

// Returns a CBOR map for the contents of the given Parameter argument
static cbor_item_t *_paramAsMap(CswParameter param) {
    cbor_item_t *map = cbor_new_definite_map(3);
    cbor_map_add(map, _cswMakeStringPair("keyName", param.keyName));
    cbor_map_add(map, _cswMakeItemPair("values", _paramValuesAsMap(param)));
    cbor_map_add(map, _cswMakeStringPair("units", param.units));
    return map;
}

// Returns a CBOR map for the given Parameter argument
cbor_item_t *_cswParameterAsMap(CswParameter param) {
    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _cswMakeItemPair(_keyTypeName(param.keyType), _paramAsMap(param)));
    return map;
}


// ---- From CBOR ---

// Since the string values returned from CBOR are not null-terminated, we need to allocate
// a null-terminated copy. Note that the return value needs to be freed at some point.
char* _cswGetString(cbor_item_t* item) {
    return strndup((char*)cbor_string_handle(item), (int)cbor_string_length(item));
}

// Returns an Parameter for the given CBOR map
CswParameter _cswParameterFromMap(cbor_item_t *map) {
    CswParameter param = {};
    for (size_t i = 0; i < cbor_map_size(map); i++) {
        struct cbor_pair pair = cbor_map_handle(map)[i];
        char *key = (char *) cbor_string_handle(pair.key);
        param.keyType = _keyTypeValue(key);

        // XXX TODO: In progress...
    }
    return param;
}

// Makes an array of CswParameters from the given CBOR Item.
// The return type is a CswStruct, since it contains an array or params as well as the length of the array.
CswParamSet _cswGetParamSet(cbor_item_t* item) {
    CswParamSet paramSet = {};
    paramSet.numParams = cbor_array_size(item);
    paramSet.params = malloc(paramSet.numParams * sizeof(CswParameter));
    for (size_t i = 0; i < paramSet.numParams; i++) {
        paramSet.params[i] = _cswParameterFromMap(cbor_array_handle(item)[i]);
    }
    return paramSet;
}

