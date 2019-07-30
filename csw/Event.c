#include <stdio.h>
#include <string.h>
#include <cbor.h>
#include <hiredis/hiredis.h>

#include "Event.h"
#include "EventTime.h"
#include "Parameter.h"

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
