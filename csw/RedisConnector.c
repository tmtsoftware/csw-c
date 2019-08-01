//
// Created by abrighto on 7/24/19.
//

#include "RedisConnector.h"

#include <stdio.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#include <malloc.h>

// --- Manage communication with Redis ---

/**
 * Opens the connection to Redis.
 *
 * @return context used for subsequent calls
 */
CswRedisConnectorContext cswRedisConnectorInit(void) {
    CswRedisConnectorContext result;
    result.redis = redisConnect("127.0.0.1", 6379);
    if (result.redis == NULL || result.redis->err) {
        if (result.redis) {
            printf("Redis Error: %s\n", result.redis->errstr);
        } else {
            printf("Redis Error: Can't allocate context\n");
        }
    }

    result.asyncRedis = redisAsyncConnect("127.0.0.1", 6379);
    if (result.asyncRedis == NULL || result.asyncRedis->err) {
        if (result.asyncRedis) {
            printf("Redis Error: %s\n", result.asyncRedis->errstr);
        } else {
            printf("Redis Error: Can't allocate async context\n");
        }
    }

    return result;
}

/**
 * Closes and frees the Redis connection.
 *
 * @param context the return value from redisConnectorInit
 */
void cswRedisConnectorClose(CswRedisConnectorContext context) {
    redisFree(context.redis);
    redisAsyncFree(context.asyncRedis);
}

// Joins array of strings together with given separator, and save in result,
// which should have the necessary space allocated
static void _join(const char **arr, int len, const char *sep, char *result) {
    if (len == 0) {
        *result = '\0';
    } else {
        strcat(result, arr[0]);
        if (len > 1) {
            strcat(result, sep);
            _join(arr + 1, len - 1, sep, result + strlen(result));
        }
    }
}

// Returns total length of the key strings in the array
static int _getTotalSize(const char **keyList, int numKeys) {
    size_t bufSize = 0;
    for (int i = 0; i < numKeys; i++)
        bufSize += strlen(keyList[i]);
    return bufSize;
}

// Internal callback used to simplify API.
static void _subscribeCallback(redisAsyncContext *asyncRedis, void *r, void *privateData) {
    redisReply *reply = r;
    if (reply == NULL) {
        printf("Redis subscribe callback with null message\n");
        return;
    }
    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3) {
        if (strcmp(reply->element[0]->str, "subscribe") != 0) {
            const char *channel = reply->element[1]->str;
            void *msg = reply->element[2]->str;
            size_t len = reply->element[2]->len;
            CswRedisConnectorCallbackData *callbackData = privateData;
            (*callbackData->callback)(channel, msg, len, callbackData->privateData);
        }
    }
}


/**
 * Subscribes to changes in the values of the given keys.
 *
 * @param context the return value from redisConnectorInit
 * @param keyList list of keys to subscribe to
 * @param numKeys number of keys in list
 * @param callback callack function to be notified
 * @param privateData caller data
 * @return an instance of RedisConnectorCallbackData if there were no errors, otherwise NULL.
 */
CswRedisConnectorCallbackData *cswRedisConnectorSubscribe(CswRedisConnectorContext context, const char **keyList, int numKeys,
                                                          CswRedisConnectorCallback callback, void *privateData) {
    int bufSize = _getTotalSize(keyList, numKeys) + numKeys;
    char keys[bufSize];
    keys[0] = '\0';
    _join(keyList, numKeys, " ", keys);
    CswRedisConnectorCallbackData *callbackData = malloc(sizeof(CswRedisConnectorCallbackData));
    callbackData->callback = callback;
    callbackData->privateData = privateData;
    int result = redisAsyncCommand(context.asyncRedis, _subscribeCallback, callbackData, "subscribe %s", keys);
    if (result != REDIS_OK) {
        printf("Redis SUBSCRIBE Error: %s\n", context.asyncRedis->errstr);
        free(callbackData);
        return NULL;
    } else {
        return callbackData;
    }
}

/**
 * Unsubscribes to changes in the values of the given keys.
 *
 * @param context the return value from redisConnectorInit
 * @param keyList list of keys to subscribe to
 * @param numKeys number of keys in list
 * @param callbackData the value returned from the redisConnectorSubscribe() call (needs to be freed, may be NULL if already freed)
 * @return 0 if there were no errors
 */
int redisConnectorUnsubscribe(CswRedisConnectorContext context, const char **keyList, int numKeys,
                              CswRedisConnectorCallbackData *callbackData) {
    int bufSize = _getTotalSize(keyList, numKeys) + numKeys;
    char keys[bufSize];
    keys[0] = '\0';
    _join(keyList, numKeys, " ", keys);
    redisReply *reply = redisCommand(context.redis, "unsubscribe %s", keys);
    int status = 0;
    if (reply == NULL) {
        printf("Redis UNSUBSCRIBE Error: %s\n", context.redis->errstr);
        status++;
    }
    if (callbackData)
        free(callbackData);

    return status;
}

/**
 * Sets and publishes the given key with the given encoded value and returns 0 if there were no errors
 *
 * @param context the return value from redisConnectorInit
 * @param key the key to publish
 * @param encodedValue the encoded value for the key
 * @param length the length in bytes of the encoded value
 * @return 0 if there were no errors
 */
int cswRedisConnectorPublish(CswRedisConnectorContext context, const char *key, const unsigned char *encodedValue, size_t length) {
    //reply = redisCommand(context, "SET foo %b", value, (size_t) valuelen);
    redisReply *reply1 = redisCommand(context.redis, "set %s %b", key, encodedValue, length);
    redisReply *reply2 = redisCommand(context.redis, "publish %s %b", key, encodedValue, length);
    int status = 0;
    if (reply1 == NULL) {
        printf("Redis SET Error: %s\n", context.redis->errstr);
        status++;
    } else {
        freeReplyObject(reply1);
    }
    if (reply2 == NULL) {
        printf("Redis PUBLISH Error: %s\n", context.redis->errstr);
        status++;
    } else {
        freeReplyObject(reply2);
    }
    return status;
}

/**
 * Gets the value for the given key
 *
 * @param context the return value from redisConnectorInit
 * @param key the key to get
 * @return the (encoded) value for the key
 */
unsigned char *cswRedisConnectorGet(CswRedisConnectorContext context, const char *key) {
    redisReply *reply = redisCommand(context.redis, "GET %s", key);
    if (reply == NULL) {
        printf("Redis Error: %s\n", context.redis->errstr);
        return NULL;
    } else {
        char *result = strdup(reply->str);
        freeReplyObject(reply);
        return (unsigned char *)result;
    }
}

