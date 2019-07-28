//
// Created by abrighto on 7/26/19.
//

#ifndef CSW_C_EVENTTIME_H
#define CSW_C_EVENTTIME_H


// An EventTime containing seconds since the epoch (1970) and the offset from seconds in nanoseconds
typedef struct {
    long seconds;
    int nanos;
} EventTime;

#endif //CSW_C_EVENTTIME_H
