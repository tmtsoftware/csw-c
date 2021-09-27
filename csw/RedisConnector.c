//
// Created by abrighto on 7/24/19.
//

#include <stdio.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#include "zlog.h"

#include "cswImpl.h"


// --- Manage communication with Redis ---

/**
 * Opens a synchronous connection to Redis.
 *
 * @return context used for subsequent calls
 */
redisContext *cswRedisInit(void) {
    redisContext *result = redisConnect("127.0.0.1", 6379);
    if (result == NULL || result->err) {
        if (result) {
            dzlog_error("Redis Error: %s\n", result->errstr);
        } else {
            dzlog_error("Redis Error: Can't allocate redis context\n");
        }
    }
    return result;
}

/**
 * Opens an asynchronous connection to Redis (for subscribing).
 *
 * @return context used for subsequent calls
 */
redisAsyncContext *cswRedisAsyncInit(void) {
    redisAsyncContext *result = redisAsyncConnect("127.0.0.1", 6379);
    if (result == NULL || result->err) {
        if (result) {
            dzlog_error("Redis Error: %s\n", result->errstr);
        } else {
            dzlog_error("Redis Error: Can't allocate async redis context\n");
        }
    }
    return result;
}

/**
 * Closes and frees the Redis publisher connection.
 *
 * @param context the return value from cswRedisInit
 */
void
cswRedisPublisherClose(redisContext *context) {
    redisFree(context);
}

/**
 * Closes and frees the Redis subscriber connection.
 *
 * @param context the return value from cswRedisAsyncInit
 */
void cswRedisSubscriberClose(redisAsyncContext *context) {
    redisAsyncFree(context);
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
        dzlog_error("Redis subscribe callback with null message\n");
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
 * @param context the return value from cswRedisAsyncInit
 * @param keyList list of keys to subscribe to
 * @param numKeys number of keys in list
 * @param callback callack function to be notified
 * @param privateData caller data
 * @return an instance of RedisConnectorCallbackData if there were no errors, otherwise NULL
 * (return value needs to be freed with free() when done).
 */
CswRedisConnectorCallbackData *cswRedisConnectorSubscribe(redisAsyncContext *context, const char **keyList, int numKeys,
                                                          CswRedisConnectorCallback callback, void *privateData) {
    int bufSize = _getTotalSize(keyList, numKeys) + numKeys;
    char keys[bufSize];
    keys[0] = '\0';
    _join(keyList, numKeys, " ", keys);
    CswRedisConnectorCallbackData *callbackData = malloc(sizeof(CswRedisConnectorCallbackData));
    callbackData->callback = callback;
    callbackData->privateData = privateData;
    int result = redisAsyncCommand(context, _subscribeCallback, callbackData, "subscribe %s", keys);
    if (result != REDIS_OK) {
        dzlog_error("Redis SUBSCRIBE Error: %s\n", context->errstr);
        free(callbackData);
        return NULL;
    } else {
        return callbackData;
    }
}

static void _unsubscribeCallback(redisAsyncContext *context, void *r, void *privateData) {
    redisReply *reply = r;
    if (reply == NULL) {
        dzlog_error("Redis UNSUBSCRIBE Error: %s\n", context->errstr);
        return;
    }
}

/**
 * Unsubscribes to changes in the values of the given keys.
 *
 * @param context the return value from cswRedisAsyncInit
 * @param keyList list of keys to subscribe to
 * @param numKeys number of keys in list
 * @param callbackData the value returned from the redisConnectorSubscribe() call (needs to be freed, may be NULL if already freed)
 * @return 0 if there were no errors
 */
int redisConnectorUnsubscribe(redisAsyncContext *context, const char **keyList, int numKeys,
                              CswRedisConnectorCallbackData *callbackData) {
    int bufSize = _getTotalSize(keyList, numKeys) + numKeys;
    char keys[bufSize];
    keys[0] = '\0';
    _join(keyList, numKeys, " ", keys);

    //int redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, const char *format, ...);
    int result = redisAsyncCommand(context, _unsubscribeCallback, NULL, "unsubscribe %s", keys);
    if (result != REDIS_OK) {
        dzlog_error("Redis UNSUBSCRIBE Error: %s\n", context->errstr);
    }
    return result;
}

/**
 * Sets and publishes the given key with the given encoded value and returns 0 if there were no errors
 *
 * @param context the return value from cswRedisInit
 * @param key the key to publish
 * @param encodedValue the encoded value for the key
 * @param length the length in bytes of the encoded value
 * @return 0 if there were no errors
 */
int cswRedisConnectorPublish(redisContext *context, const char *key, const unsigned char *encodedValue, size_t length) {
    //reply = redisCommand(context, "SET foo %b", value, (size_t) valuelen);
    redisReply *reply1 = redisCommand(context, "set %s %b", key, encodedValue, length);
    redisReply *reply2 = redisCommand(context, "publish %s %b", key, encodedValue, length);
    int status = 0;
    if (reply1 == NULL) {
        dzlog_error("Redis SET Error: %s\n", context->errstr);
        status++;
    } else {
        freeReplyObject(reply1);
    }
    if (reply2 == NULL) {
        dzlog_error("Redis PUBLISH Error: %s\n", context->errstr);
        status++;
    } else {
        freeReplyObject(reply2);
    }
    return status;
}

/**
 * Gets the value for the given key
 *
 * @param context the return value from cswRedisInit
 * @param key the key to get
 * @return a struct containing the (encoded) value for the key and the length of the value in bytes
 */
CswRedisConnectorGetResult cswRedisConnectorGet(redisContext *context, const char *key) {
    redisReply *reply = redisCommand(context, "GET %s", key);
    if (reply == NULL) {
        dzlog_error("Redis Error: %s\n", context->errstr);
        CswRedisConnectorGetResult result = {.errorMsg = context->errstr};
        return result;
    } else {
        unsigned char *data = (unsigned char *) strdup(reply->str);
        CswRedisConnectorGetResult result = {.data = data, .length = reply->len};
        freeReplyObject(reply);
        return result;
    }
}

