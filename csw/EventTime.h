//
// Created by abrighto on 7/26/19.
//

#ifndef CSW_C_EVENTTIME_H
#define CSW_C_EVENTTIME_H


// An EventTime containing seconds since the epoch (1970) and the offset from seconds in nanoseconds
typedef struct {
    long seconds;
    int nanos;
} CswEventTime;

// Returns a CBOR map for the given EventTime argument
cbor_item_t *_cswEventTimeAsMap(CswEventTime et);

// Returns an EventTime for the given CBOR map
CswEventTime _cswEventTimeFromMap(cbor_item_t* map);

/**
 * Returns an instance containing the current time
 */
CswEventTime cswEventTime();

/**
 * Constructor
 */
CswEventTime cswMakeEventTime(long seconds, int nanos);


#endif //CSW_C_EVENTTIME_H
