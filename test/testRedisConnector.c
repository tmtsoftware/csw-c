//
// Created by abrighto on 7/25/19.
//

#include <csw/RedisConnector.h>
#include <assert.h>
#include <string.h>

#include <stdio.h>
#include <hiredis/adapters/libev.h>

static void callback(const char *key, const unsigned char *value, size_t len, void *privateData) {
    printf("Subscribe callback: %s = %s\n", key, value);
}

int main() {
    CswRedisConnectorContext context = cswRedisConnectorInit();
    assert(context.redis != NULL && context.asyncRedis != NULL);

    redisLibevAttach(EV_DEFAULT, context.asyncRedis);

    // -- publish --
    const char *key = "mytestkey1";
    const char *encodedValue = "abcdef";
    int pubStatus = cswRedisConnectorPublish(context, key, (unsigned char*)encodedValue, strlen(encodedValue));
    assert(pubStatus == 0);

    // -- get --
    CswRedisConnectorGetResult res1 = cswRedisConnectorGet(context, key);
    assert(strncmp((char*)res1.data, encodedValue, res1.length) == 0);

    // -- subscribe --
    const char *keyList[1] = {key};
    CswRedisConnectorCallbackData* callbackData = cswRedisConnectorSubscribe(context, keyList, 1, callback, NULL);
    assert(callbackData != NULL);

//    int pubStatus2 = cswRedisConnectorPublish(context, key, (unsigned char*)"12345", 5);
//    assert(pubStatus2 == 0);
//    assert(strcmp((char*)cswRedisConnectorGet(context, key), "12345") == 0);
//
//    int pubStatus3 = cswRedisConnectorPublish(context, key, (unsigned char*)"Test message", strlen("\"Test message\""));
//    assert(pubStatus3 == 0);
//    assert(strcmp((char*)cswRedisConnectorGet(context, key), "Test message") == 0);

    ev_loop(EV_DEFAULT_ 0);
    return 0;
}
