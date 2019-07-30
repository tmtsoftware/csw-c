#ifndef CSW_C_EVENT_H
#define CSW_C_EVENT_H

#include "Parameter.h"
#include "EventTime.h"

typedef enum {
    SystemEvent,
    ObserveEvent
} CswEventType;

/**
 * An Event that can be published to the event service
 */
typedef struct {
    // SystemEvent or ObserveEvent (not encoded)
    CswEventType eventType;

    // prefix representing source of the event
    char* source;

    // the name of event
    char* eventName;

    // list of CswParameter (keys with values)
    CswParameter* paramSet;

    // Number of parameters in the paramSet (not encoded)
    int numParams;

    // the time the event was created (defaults to current time)
    CswEventTime eventTime;

    // event id (optional: Should leave empty unless received from event service)
    char* eventId;
} CswEvent;


#endif //CSW_C_EVENT_H