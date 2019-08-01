//
// Created by abrighto on 7/31/19.
//

#ifndef CSW_C_EVENTPUBLISHER_H
#define CSW_C_EVENTPUBLISHER_H

#include "RedisConnector.h"

typedef struct {
    CswRedisConnectorContext redisConnectorContext;
} CswEventPublisherContext;

/**
 * Initializes the event publisher
 * @return context to be used on subsequent calls
 */
CswEventPublisherContext cswEventPublisherInit();

/**
 * Publishes an event to the Event Service
 *
 * @param context return value from cswEventPublisherInit()
 * @param event Event event: Event to be published
 * @return 0 if OK, otherwise a non-zero value
 */
int cswEventPublisherPublish(CswEventPublisherContext context, CswEvent event);

#endif //CSW_C_EVENTPUBLISHER_H
