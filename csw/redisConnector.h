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
} RedisConnectorContext;

typedef void (*RedisConnectorCallback)(const char *key, const char *value, void *privateData);

typedef struct {
    RedisConnectorCallback callback;
    void *privateData;
} RedisConnectorCallbackData;

RedisConnectorContext redisConnectorInit(void);

void redisConnectorClose(RedisConnectorContext context);

int redisConnectorSubscribeCallback(RedisConnectorContext context, const char **keyList, int numKeys,
                                    RedisConnectorCallback callback, void *privateData);

int redisConnectorPublish(RedisConnectorContext context, const char *key, const char *encodedValue);

char *redisConnectorGet(RedisConnectorContext context, const char *key);


#endif //CSW_C_REDISCONNECTOR_H
