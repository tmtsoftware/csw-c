//
// Created by abrighto on 7/31/19.
//

#include <string.h>
#include <cbor.h>
#include "csw.h"
#include "cswImpl.h"

/**
 * Initializes the event publisher
 * @return context to be used on subsequent calls
 */
CswEventServiceContext cswEventPublisherInit() {
    redisContext* context = cswRedisInit();
    assert(context != NULL);
    return context;
}

/**
 * Closes and frees the CSW event publisher connection.
 *
 * @param context the return value from cswEventPublisherInit()
 */
void cswEventPublisherClose(CswEventServiceContext context) {
    cswRedisPublisherClose(context);
}


/**
 * Publishes an event to the Event Service
 *
 * @param context return value from cswEventPublisherInit()
 * @param event Event event: Event to be published
 * @return 0 if OK, otherwise a non-zero value
 */
int cswEventPublish(CswEventServiceContext context, CswEvent event) {
    size_t keyLen = strlen(event.source) + 1 + strlen(event.eventName);
    char eventKey[keyLen];
    sprintf(eventKey, "%s.%s", event.source, event.eventName);
    cbor_item_t *item = cswEventAsMap(event);
    unsigned char *buffer;
    size_t buffer_size, length = cbor_serialize_alloc(item, &buffer, &buffer_size);
    int status = cswRedisConnectorPublish(context, eventKey, buffer, length);

//    // Pretty-print the result
//    cbor_describe(item, stdout);
//    fflush(stdout);

    // Deallocate the result
    free(buffer);
    cbor_decref(&item);

    return status;
}