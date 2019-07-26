#ifndef CSW_C_EVENT_H
#define CSW_C_EVENT_H

#include "Parameter.h"
#include "EventTime.h"
/**
 * An Event that can be published to the event service
 */
typedef struct {
    // prefix representing source of the event
    char* source;

    // the name of event
    char* eventName;

    // list of Parameter (keys with values)
    Parameter* paramSet;

    // the time the event was created (defaults to current time)
    EventTime eventTime;

    // event id (optional: Should leave empty unless received from event service)
    char* eventId;
} Event;


#endif //CSW_C_EVENT_H