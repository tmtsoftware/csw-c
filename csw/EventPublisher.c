//
// Created by abrighto on 7/31/19.
//

#include <string.h>
#include <cbor.h>
#include "Event.h"
#include "RedisConnector.h"
#include "EventPublisher.h"

/**
 * Initializes the event publisher
 * @return context to be used on subsequent calls
 */
CswEventPublisherContext cswEventPublisherInit() {
    CswEventPublisherContext context = {.redisConnectorContext = cswRedisConnectorInit()};
    assert(context.redisConnectorContext.redis != NULL && context.redisConnectorContext.asyncRedis != NULL);
    return context;
}

/**
 * Publishes an event to the Event Service
 *
 * @param context return value from cswEventPublisherInit()
 * @param event Event event: Event to be published
 * @return 0 if OK, otherwise a non-zero value
 */
int cswEventPublisherPublish(CswEventPublisherContext context, CswEvent event) {
    size_t keyLen = strlen(event.source) + 1 + strlen(event.eventName);
    char eventKey[keyLen];
    sprintf(eventKey, "%s.%s", event.source, event.eventName);
    cbor_item_t *item = cswEventAsMap(event);
    unsigned char *buffer;
    size_t buffer_size, length = cbor_serialize_alloc(item, &buffer, &buffer_size);
    int status = cswRedisConnectorPublish(context.redisConnectorContext, eventKey, buffer, length);

//    // Pretty-print the result
//    cbor_describe(item, stdout);
//    fflush(stdout);

    // Deallocate the result
    free(buffer);
    cbor_decref(&item);

    return status;
}