//
// Created by abrighto on 7/26/19.
//

#include <string.h>
#include <cbor.h>
#include "Parameter.h"

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

static cbor_item_t *_makeStringItem(void *value) {
    return cbor_move(cbor_build_string(value));
}

static cbor_item_t *_makeLongItem(void *value) {
    long v = *(long *) value;
    if (v < 0)
        return cbor_move(cbor_build_negint64(v));
    else
        return cbor_move(cbor_build_uint64(v));
}

static cbor_item_t *_makeIntItem(void *value) {
    int v = *(int *) value;
    if (v < 0)
        return cbor_move(cbor_build_negint32(v));
    else
        return cbor_move(cbor_build_uint32(v));
}

static cbor_item_t *_makeShortItem(void *value) {
    short v = *(short *) value;
    if (v < 0)
        return cbor_move(cbor_build_negint16(v));
    else
        return cbor_move(cbor_build_uint16(v));
}

// XXX TODO: make UTF8 compatible?
static cbor_item_t *_makeCharItem(void *value) {
    signed char v = *(signed char *) value;
    if (v < 0)
        return cbor_move(cbor_build_negint8(v));
    else
        return cbor_move(cbor_build_uint8(v));
}

static cbor_item_t *_makeFloatItem(void *value) {
    float v = *(float *) value;
    return cbor_move(cbor_build_float4(v));
}

static cbor_item_t *_makeDoubleItem(void *value) {
    double v = *(double *) value;
    return cbor_move(cbor_build_float8(v));
}

static cbor_item_t *_makeBooleanItem(void *value) {
    bool v = *(bool *) value;
    return cbor_move(cbor_build_bool(v));
}

static cbor_item_t *_arrayValueAsItem(KeyType keyType, void *values, int index);

static cbor_item_t *_makeArrayItem(KeyType keyType, ArrayValue *values) {
    cbor_item_t *array = cbor_new_definite_array(values->numValues);
    for (int i = 0; i < values->numValues; i++) {
        cbor_array_push(array, _arrayValueAsItem(keyType, values->values, i));
    }
    return array;
}

static cbor_item_t *_makeMatrixItem(KeyType keyType, ArrayValue *values) {
    cbor_item_t *array = cbor_new_definite_array(values->numValues);
    for (int i = 0; i < values->numValues; i++) {
        cbor_array_push(array, _makeArrayItem(keyType, (ArrayValue*)(values->values + i)));
    }
    return array;
}

static cbor_item_t *_makeStructItem(void *value) {
    Struct* myStruct = (Struct*)value;
    cbor_item_t *array = cbor_new_definite_array(myStruct->numParams);
    for (int i = 0; i < myStruct->numParams; i++) {
        cbor_array_push(array, parameterAsMap(myStruct->paramSet[i]));
    }
    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map,
                 (struct cbor_pair) {
                         .key = cbor_move(cbor_build_string("paramSet")),
                         .value = array});
    return map;
}

// Returns a cbor item for the parameter value at the given index
static cbor_item_t *_arrayValueAsItem(KeyType keyType, void *values, int index) {
    void *value = values + index;
    switch (keyType) {
        case ChoiceKey:
        case UTCTimeKey:
        case TAITimeKey:
        case StringKey:
            return _makeStringItem(value);
        case StructKey:
            return _makeStructItem(value);
        case RaDecKey:
            return "RaDecKey";
        case EqCoordKey:
            return "EqCoordKey";
        case SolarSystemCoordKey:
            return "SolarSystemCoordKey";
        case MinorPlanetCoordKey:
            return "MinorPlanetCoordKey";
        case CometCoordKey:
            return "CometCoordKey";
        case AltAzCoordKey:
            return "AltAzCoordKey";
        case CoordKey:
            return "CoordKey";
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
    cbor_map_add(map,
                 (struct cbor_pair) {
                         .key = cbor_move(cbor_build_string("keyName")),
                         .value = cbor_move(cbor_build_string(param.keyName))});
    cbor_map_add(map,
                 (struct cbor_pair) {
                         .key = cbor_move(cbor_build_string("values")),
                         .value = cbor_move(_paramValuesAsMap(param))});
    cbor_map_add(map,
                 (struct cbor_pair) {
                         .key = cbor_move(cbor_build_string("units")),
                         .value = cbor_move(cbor_build_string(param.units))});
    return map;
}

// Returns a CBOR map for the given Parameter argument
cbor_item_t *parameterAsMap(Parameter param) {
    cbor_item_t *map = cbor_new_definite_map(1);
    cbor_map_add(map,
                 (struct cbor_pair) {
                         .key = cbor_move(cbor_build_string(_keyTypeName(param.keyType))),
                         .value = _paramAsMap(param)});
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