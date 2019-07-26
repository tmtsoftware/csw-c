//
// Created by abrighto on 7/26/19.
//

#ifndef CSW_C_PARAMETER_H
#define CSW_C_PARAMETER_H


// A Parameter (keys with values, units).
// See https://tmtsoftware.github.io/csw/0.7.0-RC1/messages/keys-parameters.html for key type names.
// See https://tmtsoftware.github.io/csw/0.7.0-RC1/messages/units.html for list of unit names.
// 'items' is an array of values, or a nested array for array and matrix types.
typedef struct {
    char* keyType;
    void* items;
    char* units;
} Parameter;

#endif //CSW_C_PARAMETER_H
