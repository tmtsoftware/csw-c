//
// Created by abrighto on 7/24/19.
//

#ifndef CSW_C_REDISCONNECTOR_H
#define CSW_C_REDISCONNECTOR_H

#include <hiredis/hiredis.h>
#include <hiredis/async.h>

typedef struct {
    redisContext *redis;
    redisAsyncContext *asyncRedis;
} CswRedisConnectorContext;

typedef void (*CswRedisConnectorCallback)(const char *key, const char *value, void *privateData);

typedef struct {
    CswRedisConnectorCallback callback;
    void *privateData;
} CswRedisConnectorCallbackData;

CswRedisConnectorContext cswRedisConnectorInit(void);

void cswRedisConnectorClose(CswRedisConnectorContext context);

CswRedisConnectorCallbackData* cswRedisConnectorSubscribe(CswRedisConnectorContext context, const char **keyList, int numKeys,
                                                          CswRedisConnectorCallback callback, void *privateData);

int cswRedisConnectorPublish(CswRedisConnectorContext context, const char *key, const char *encodedValue);

char *cswRedisConnectorGet(CswRedisConnectorContext context, const char *key);


#endif //CSW_C_REDISCONNECTOR_H
