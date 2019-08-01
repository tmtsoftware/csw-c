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

typedef void (*CswRedisConnectorCallback)(const char *key, const unsigned char *value, size_t len, void *privateData);

typedef struct {
    CswRedisConnectorCallback callback;
    void *privateData;
} CswRedisConnectorCallbackData;

typedef struct {
    size_t length;
    unsigned char* data;
    char* errorMsg;  // Set if there was an error
} CswRedisConnectorGetResult;

CswRedisConnectorContext cswRedisConnectorInit(void);

void cswRedisConnectorClose(CswRedisConnectorContext context);

CswRedisConnectorCallbackData* cswRedisConnectorSubscribe(CswRedisConnectorContext context, const char **keyList, int numKeys,
                                                          CswRedisConnectorCallback callback, void *privateData);

/**
 * Sets and publishes the given key with the given encoded value and returns 0 if there were no errors
 *
 * @param context the return value from redisConnectorInit
 * @param key the key to publish
 * @param encodedValue the encoded value for the key
 * @param length the length in bytes of the encoded value
 * @return 0 if there were no errors
 */
int cswRedisConnectorPublish(CswRedisConnectorContext context, const char *key, const unsigned char *encodedValue, size_t length);

/**
 * Gets the value for the given key
 *
 * @param context the return value from redisConnectorInit
 * @param key the key to get
 * @return a struct containing the (encoded) value for the key and the length of the value in bytes
 */
CswRedisConnectorGetResult cswRedisConnectorGet(CswRedisConnectorContext context, const char *key);


#endif //CSW_C_REDISCONNECTOR_H
