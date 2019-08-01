//
// Created by abrighto on 7/28/19.
//

#include <string.h>
#include <cbor.h>
#include <time.h>
#include "EventTime.h"

/**
 * Returns an instance containing the current time
 */
CswEventTime cswEventTime() {
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    CswEventTime result = {.seconds = tp.tv_sec, .nanos = tp.tv_nsec};
    return result;
}

/**
 * Constructor
 */
CswEventTime cswMakeEventTime(long seconds, int nanos) {
    CswEventTime t = {.seconds = seconds, .nanos = nanos};
    return t;
}

// Returns a CBOR map for the given EventTime argument
cbor_item_t *_cswEventTimeAsMap(CswEventTime et) {
    cbor_item_t *map = cbor_new_definite_map(2);
    cbor_map_add(map,
                 (struct cbor_pair) {
                         .key = cbor_move(cbor_build_string("seconds")),
                         .value = cbor_move(cbor_build_uint64(et.seconds))});
    cbor_map_add(map,
                 (struct cbor_pair) {
                         .key = cbor_move(cbor_build_string("nanos")),
                         .value = cbor_move(cbor_build_uint32(et.nanos))});
    return map;
}

// Returns an EventTime for the given CBOR map
CswEventTime _cswEventTimeFromMap(cbor_item_t *map) {
    CswEventTime et = {};
    for (size_t i = 0; i < cbor_map_size(map); i++) {
        struct cbor_pair pair = cbor_map_handle(map)[i];
        /* Note: no null at end of string */
        char *key = (char *) cbor_string_handle(pair.key);
        if (strncmp(key, "seconds", cbor_string_length(pair.key)) == 0) {
            et.seconds = cbor_get_int(pair.value);
        } else if (strncmp(key, "nanos", cbor_string_length(pair.key)) == 0) {
            et.nanos = cbor_get_int(pair.value);
        }
    }
    return et;
}