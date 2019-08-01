#include <string.h>
#include <cbor.h>
#include <uuid/uuid.h>

#include "Event.h"
#include "EventTime.h"
#include "Parameter.h"


// Returns a new uuid string
static char *makeId(void) {
    // typedef unsigned char uuid_t[16];
    uuid_t uuid;

    // generate
    uuid_generate(uuid);

    // unparse (to string)
    char* uuid_str = malloc(37);      // ex. "1b4e28ba-2fa1-11d2-883f-0016d3cca427" + "\0"
    uuid_unparse_lower(uuid, uuid_str);
    return uuid_str;
}

/**
 * Event constructor
 */
CswEvent cswMakeEvent(CswEventType eventType, const char* source, const char* eventName, CswParamSet paramSet) {
    CswEvent event = {
            .eventType = eventType,
            .source = source,
            .eventName = eventName,
            .paramSet = paramSet.params,
            .numParams = paramSet.numParams,
            .eventTime = cswEventTime(),
            .eventId = makeId()
    };
    return event;
}

// Returns a CBOR map for the given Event argument
cbor_item_t *cswEventAsMap(CswEvent event) {
    cbor_item_t *valueMap = cbor_new_definite_map(5);
    cbor_map_add(valueMap, _cswMakeStringPair("source", event.source));
    cbor_map_add(valueMap, _cswMakeStringPair("eventName", event.eventName));
    cbor_map_add(valueMap, _cswMakeParamSetItemPair(event.paramSet, event.numParams));
    cbor_map_add(valueMap, _cswMakeItemPair("eventTime", _cswEventTimeAsMap(event.eventTime)));
    cbor_map_add(valueMap, _cswMakeStringPair("eventId", event.eventId));

    cbor_item_t *map = cbor_new_definite_map(1);
    char* eventType = "SystemEvent";
    if (event.eventType == ObserveEvent)
        eventType = "ObserveEvent";
    cbor_map_add(map, _cswMakeItemPair(eventType, valueMap));
    return map;
}


// Returns an Event for the given CBOR map
CswEvent _cswEventFromMap(cbor_item_t* map) {
    CswEvent event = {};
    for (size_t i = 0; i < cbor_map_size(map); i++) {
        struct cbor_pair pair = cbor_map_handle(map)[i];
        /* Note: no null at end of string */
        char* key = (char*)cbor_string_handle(pair.key);
        int keyLen = cbor_string_length(pair.key);
        if (strncmp(key, "source", keyLen) == 0) {
            event.source = _cswGetString(pair.value);
        } else if (strncmp(key, "eventName", keyLen) == 0) {
            event.eventName = _cswGetString(pair.value);
        } else if (strncmp(key, "paramSet", keyLen) == 0) {
            // XXX FIXME: TODO: complete this code...
//            event.paramSet = _cswMakeParamSet(pair.value);
        }
    }
    return event;
}

// Frees any allocated memory for the given event
void cswFreeEvent(CswEvent event) {
    // XXX TODO ...
}
