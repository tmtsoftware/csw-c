#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-reserved-identifier"
//
// Created by abrighto on 8/6/19.
//

#ifndef CSW_C_CSWIMPL_H
#define CSW_C_CSWIMPL_H

#include "csw.h"
#include <cbor.h>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>

// Private implementation related definitions

// --- Events ---

// Returns a CBOR map for the given Event argument
cbor_item_t *cswEventAsMap(CswEvent event);

// Returns a CBOR map for the given EventTime argument
cbor_item_t *_cswEventTimeAsMap(CswEventTime et);

// Returns an EventTime for the given CBOR map
CswEventTime _cswEventTimeFromMap(cbor_item_t* map);


// --- Parameters ---

cbor_item_t *_cswParameterAsMap(CswParameter param);
cbor_item_t *_cswUtcTimeAsMap(CswUtcTime t);
cbor_item_t *_cswTaiTimeAsMap(CswTaiTime t);

struct cbor_pair _cswMakeStringPair(const char *key, const char *value);
struct cbor_pair _cswMakeItemPair(const char *key, cbor_item_t *value);
struct cbor_pair _cswMakeParamSetItemPair(const CswParameter* paramSet, int numParams);
char* _cswGetString(cbor_item_t* item);

// --- Redis ---

typedef void (*CswRedisConnectorCallback)(const char *key, const unsigned char *value, size_t len, void *privateData);

//typedef struct {
//    redisContext *redis;
//    redisAsyncContext *asyncRedis;
//} CswRedisConnectorContext;

typedef struct {
    CswRedisConnectorCallback callback;
    void *privateData;
} CswRedisConnectorCallbackData;

typedef struct {
    size_t length;
    unsigned char* data;
    char* errorMsg;  // Set if there was an error
} CswRedisConnectorGetResult;

// --- Private API ---

redisContext* cswRedisInit(void);
redisAsyncContext* cswRedisAsyncInit(void);
void cswRedisPublisherClose(redisContext* context);
void cswRedisSubscriberClose(redisAsyncContext* context);

CswRedisConnectorCallbackData* cswRedisConnectorSubscribe(redisAsyncContext* context, const char **keyList, int numKeys,
                                                          CswRedisConnectorCallback callback, void *privateData);

int redisConnectorUnsubscribe(redisAsyncContext* context, const char **keyList, int numKeys,
                              CswRedisConnectorCallbackData *callbackData);


/**
 * Sets and publishes the given key with the given encoded value and returns 0 if there were no errors
 *
 * @param context the return value from redisConnectorInit
 * @param key the key to publish
 * @param encodedValue the encoded value for the key
 * @param length the length in bytes of the encoded value
 * @return 0 if there were no errors
 */
int cswRedisConnectorPublish(redisContext* context, const char *key, const unsigned char *encodedValue, size_t length);

/**
 * Gets the value for the given key
 *
 * @param context the return value from redisConnectorInit
 * @param key the key to get
 * @return a struct containing the (encoded) value for the key and the length of the value in bytes
 */
CswRedisConnectorGetResult cswRedisConnectorGet(redisContext* context, const char *key);


#endif //CSW_C_CSWIMPL_H

#pragma clang diagnostic pop