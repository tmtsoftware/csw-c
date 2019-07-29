//
// Created by abrighto on 7/26/19.
//

#include <string.h>
#include <cbor.h>
#include "Parameter.h"
#include "Coords.h"


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
static const char *_keyTypeName(KeyType keyType) {
    return _keyTypeNames[keyType];
}

// Gets the enum value for the given key type
static KeyType _keyTypeValue(const char *keyTypeName) {
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
static const char *_eqFrameName(EqFrame eqFrame) {
    return _eqFrameNames[eqFrame];
}

// Gets the enum value for the given EQFrame name
static EqFrame _eqFrameValue(const char *eqFrameName) {
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

// Gets the name for the given SolarSystemObject enum value
static const char *_solarSystemObjectName(SolarSystemObject solarSystemObject) {
    return _solarSystemObjectNames[solarSystemObject];
}

// Gets the enum value for the given EQFrame name
static SolarSystemObject _solarSystemObjectValue(const char *solarSystemObjectName) {
    for (int i = 0; i < numSolarSystemObjects; i++) {
        if (strncmp(_solarSystemObjectNames[i], solarSystemObjectName, strlen(_solarSystemObjectNames[i])) == 0) {
            return i;
        }
    }
    return -1;
}

// ----

static cbor_item_t *_makeStringItem(const void *value) {
    return cbor_move(cbor_build_string(value));
}

static cbor_item_t *_makeLongItem(const void *value) {
    long v = *(long *) value;
    if (v < 0)
        return cbor_move(cbor_build_negint64(v));
    else
        return cbor_move(cbor_build_uint64(v));
}

static cbor_item_t *_makeIntItem(const void *value) {
    int v = *(int *) value;
    if (v < 0)
        return cbor_move(cbor_build_negint32(v));
    else
        return cbor_move(cbor_build_uint32(v));
}

static cbor_item_t *_makeShortItem(const void *value) {
    short v = *(short *) value;
    if (v < 0)
        return cbor_move(cbor_build_negint16(v));
    else
        return cbor_move(cbor_build_uint16(v));
}

// XXX TODO: make UTF8 compatible?
static cbor_item_t *_makeCharItem(const void *value) {
    signed char v = *(signed char *) value;
    if (v < 0)
        return cbor_move(cbor_build_negint8(v));
    else
        return cbor_move(cbor_build_uint8(v));
}

static cbor_item_t *_makeFloatItem(const void *value) {
    float v = *(float *) value;
    return cbor_move(cbor_build_float4(v));
}

static cbor_item_t *_makeDoubleItem(const void *value) {
    double v = *(double *) value;
    return cbor_move(cbor_build_float8(v));
}

static cbor_item_t *_makeBooleanItem(const void *value) {
    bool v = *(bool *) value;
    return cbor_move(cbor_build_bool(v));
}

static cbor_item_t *_arrayValueAsItem(KeyType keyType, const void *values, int index);

static cbor_item_t *_makeArrayItem(KeyType keyType, const ArrayValue *values) {
    cbor_item_t *array = cbor_new_definite_array(values->numValues);
    for (int i = 0; i < values->numValues; i++) {
        cbor_array_push(array, _arrayValueAsItem(keyType, values->values, i));
    }
    return array;
}

static cbor_item_t *_makeMatrixItem(KeyType keyType, const ArrayValue *values) {
    cbor_item_t *array = cbor_new_definite_array(values->numValues);
    for (int i = 0; i < values->numValues; i++) {
        cbor_array_push(array, _makeArrayItem(keyType, (ArrayValue *) (values->values + i)));
    }
    return array;
}


static struct cbor_pair _makeStringPair(const char *key, const char *value) {
    return (struct cbor_pair) {
            .key = _makeStringItem(key),
            .value = _makeStringItem(value)
    };
}

static struct cbor_pair _makeIntPair(const char *key, int value) {
    return (struct cbor_pair) {
            .key = _makeStringItem(key),
            .value = _makeIntItem(&value)
    };
}

static struct cbor_pair _makeFloatPair(const char *key, float value) {
    return (struct cbor_pair) {
            .key = _makeStringItem(key),
            .value = _makeFloatItem(&value)
    };
}

static struct cbor_pair _makeItemPair(const char *key, cbor_item_t *value) {
    return (struct cbor_pair) {
            .key = _makeStringItem(key),
            .value = cbor_move(value)
    };
}

static cbor_item_t *_makeStructItem(const void *value) {
    Struct *myStruct = (Struct *) value;
    cbor_item_t *array = cbor_new_definite_array(myStruct->numParams);
    for (int i = 0; i < myStruct->numParams; i++) {
        cbor_array_push(array, parameterAsMap(myStruct->paramSet[i]));
    }
    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _makeItemPair("paramSet", array));
    return map;
}

static cbor_item_t *_makeEqCoordItem(EqCoord *value) {
    cbor_item_t *valueMap = cbor_new_definite_map(6);
    cbor_map_add(valueMap, _makeStringPair("tag", value->tag.name));
    cbor_map_add(valueMap, _makeIntPair("dec", value->dec.uas));
    cbor_map_add(valueMap, _makeStringPair("frame", _eqFrameName(value->frame)));
    cbor_map_add(valueMap, _makeStringPair("catalogName", value->catalogName));

    cbor_item_t *pmMap = cbor_new_definite_map(2);
    cbor_map_add(pmMap, _makeFloatPair("pmx", value->pm.pmx));
    cbor_map_add(pmMap, _makeFloatPair("pmy", value->pm.pmy));
    cbor_map_add(valueMap, _makeItemPair("pm", pmMap));

    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _makeItemPair("EqCoord", valueMap));
    return map;
}

static cbor_item_t *_makeSolarSystemCoordItem(const SolarSystemCoord *value) {
    cbor_item_t *valueMap = cbor_new_definite_map(2);
    cbor_map_add(valueMap, _makeStringPair("tag", value->tag.name));
    cbor_map_add(valueMap, _makeStringPair("frame", _solarSystemObjectName(value->body)));

    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _makeItemPair("SolarSystemCoord", valueMap));
    return map;
}

static cbor_item_t *_makeMinorPlanetCoordItem(const MinorPlanetCoord *value) {
    cbor_item_t *valueMap = cbor_new_definite_map(8);
    cbor_map_add(valueMap, _makeStringPair("tag", value->tag.name));
    cbor_map_add(valueMap, _makeFloatPair("epoch", value->epoch));
    cbor_map_add(valueMap, _makeIntPair("inclination", value->inclination.uas));
    cbor_map_add(valueMap, _makeIntPair("longAscendingNode", value->longAscendingNode.uas));
    cbor_map_add(valueMap, _makeIntPair("argOfPerihelion", value->argOfPerihelion.uas));
    cbor_map_add(valueMap, _makeFloatPair("meanDistance", value->meanDistance));
    cbor_map_add(valueMap, _makeFloatPair("eccentricity", value->eccentricity));
    cbor_map_add(valueMap, _makeIntPair("meanAnomaly", value->meanAnomaly.uas));

    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _makeItemPair("MinorPlanetCoord", valueMap));
    return map;
}

static cbor_item_t *_makeCometCoordItem(const CometCoord *value) {
    cbor_item_t *valueMap = cbor_new_definite_map(7);
    cbor_map_add(valueMap, _makeStringPair("tag", value->tag.name));
    cbor_map_add(valueMap, _makeFloatPair("epochOfPerihelion", value->epochOfPerihelion));
    cbor_map_add(valueMap, _makeIntPair("inclination", value->inclination.uas));
    cbor_map_add(valueMap, _makeIntPair("longAscendingNode", value->longAscendingNode.uas));
    cbor_map_add(valueMap, _makeIntPair("argOfPerihelion", value->argOfPerihelion.uas));
    cbor_map_add(valueMap, _makeFloatPair("perihelionDistance", value->perihelionDistance));
    cbor_map_add(valueMap, _makeFloatPair("eccentricity", value->eccentricity));

    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _makeItemPair("CometCoord", valueMap));
    return map;
}

static cbor_item_t *_makeAltAzCoordItem(const AltAzCoord *value) {
    cbor_item_t *valueMap = cbor_new_definite_map(3);
    cbor_map_add(valueMap, _makeStringPair("tag", value->tag.name));
    cbor_map_add(valueMap, _makeIntPair("alt", value->alt.uas));
    cbor_map_add(valueMap, _makeIntPair("az", value->az.uas));

    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _makeItemPair("AltAzCoord", valueMap));
    return map;
}

static cbor_item_t *_makeCoordItem(const void *value) {
    Coord *coord = (Coord *) value;
    switch (coord->keyType) {
        case EqCoordKeyType:
            return _makeEqCoordItem((EqCoord *) value);
        case SolarSystemCoordKeyType:
            return _makeSolarSystemCoordItem((SolarSystemCoord *) value);
        case MinorPlanetCoordKeyType:
            return _makeMinorPlanetCoordItem((MinorPlanetCoord *) value);
        case CometCoordKeyType:
            return _makeCometCoordItem((CometCoord *) value);
        case AltAzCoordKeyType:
            return _makeAltAzCoordItem((AltAzCoord *) value);
    }
}


// Returns a cbor item for the parameter value at the given index
static cbor_item_t *_arrayValueAsItem(KeyType keyType, const void *values, int index) {
    const void *value = values + index;
    switch (keyType) {
        case ChoiceKey:
        case UTCTimeKey:
        case TAITimeKey:
        case StringKey:
            return _makeStringItem(value);
        case StructKey:
            return _makeStructItem(value);
        case RaDecKey:
            return NULL; // TODO: FIXME
        case EqCoordKey:
            return _makeCoordItem(value);
        case SolarSystemCoordKey:
            return _makeSolarSystemCoordItem(value);
        case MinorPlanetCoordKey:
            return _makeMinorPlanetCoordItem(value);
        case CometCoordKey:
            return _makeCometCoordItem(value);
        case AltAzCoordKey:
            return _makeAltAzCoordItem(value);
        case CoordKey:
            return _makeCoordItem(value);
        case BooleanKey:
            return _makeBooleanItem(value);
        case CharKey:
            return _makeCharItem(value);
        case ByteKey:
            return _makeCharItem(value);
        case ShortKey:
            return _makeShortItem(value);
        case LongKey:
            return _makeLongItem(value);
        case IntKey:
            return _makeIntItem(value);
        case FloatKey:
            return _makeFloatItem(value);
        case DoubleKey:
            return _makeDoubleItem(value);
        case ByteArrayKey: {
            // TODO: Test this
//            return _makeArrayItem(ByteKey, (ArrayValue *) value);
            ArrayValue *ar = (ArrayValue *) value;
            return cbor_build_bytestring((const unsigned char *) ar->values, ar->numValues);
        }
        case ShortArrayKey:
            return _makeArrayItem(ShortKey, (ArrayValue *) value);
        case LongArrayKey:
            return _makeArrayItem(LongKey, (ArrayValue *) value);
        case IntArrayKey:
            return _makeArrayItem(IntKey, (ArrayValue *) value);
        case FloatArrayKey:
            return _makeArrayItem(FloatKey, (ArrayValue *) value);
        case DoubleArrayKey:
            return _makeArrayItem(DoubleKey, (ArrayValue *) value);
        case ByteMatrixKey:
            return _makeMatrixItem(ByteKey, (ArrayValue *) value);
        case ShortMatrixKey:
            return _makeMatrixItem(ShortKey, (ArrayValue *) value);
        case LongMatrixKey:
            return _makeMatrixItem(LongKey, (ArrayValue *) value);
        case IntMatrixKey:
            return _makeMatrixItem(IntKey, (ArrayValue *) value);
        case FloatMatrixKey:
            return _makeMatrixItem(FloatKey, (ArrayValue *) value);
        case DoubleMatrixKey:
            return _makeMatrixItem(DoubleKey, (ArrayValue *) value);
        default:
            return NULL;
    }
}

static cbor_item_t *_paramValuesAsMap(Parameter param) {
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
static cbor_item_t *_paramAsMap(Parameter param) {
    cbor_item_t *map = cbor_new_definite_map(3);
    cbor_map_add(map, _makeStringPair("keyName", param.keyName));
    cbor_map_add(map, _makeItemPair("values", _paramValuesAsMap(param)));
    cbor_map_add(map, _makeStringPair("units", param.units));
    return map;
}

// Returns a CBOR map for the given Parameter argument
cbor_item_t *parameterAsMap(Parameter param) {
    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map, _makeItemPair(_keyTypeName(param.keyType), _paramAsMap(param)));
    return map;
}



//// Returns an Parameter for the given CBOR map
//Parameter parameterFromMap(cbor_item_t *map) {
//    Parameter param = {};
//    for (size_t i = 0; i < cbor_map_size(map); i++) {
//        struct cbor_pair pair = cbor_map_handle(map)[i];
//        char *key = (char *) cbor_string_handle(pair.key);
//        if (strncmp(key, "seconds", cbor_string_length(pair.key)) == 0) {
//            param.seconds = cbor_get_int(pair.value);
//        } else if (strncmp(key, "nanos", cbor_string_length(pair.key)) == 0) {
//            param.nanos = cbor_get_int(pair.value);
//        }
//    }
//    return param;
//}