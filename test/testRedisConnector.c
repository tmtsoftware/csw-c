//
// Created by abrighto on 7/25/19.
//

#include <csw/RedisConnector.h>
#include <assert.h>
#include <string.h>

#include <stdio.h>
#include <hiredis/adapters/libev.h>

static void callback(const char *key, const char *value, void *privateData) {
    printf("Subscribe callback: %s = %s\n", key, value);
}

int main() {
    RedisConnectorContext context = redisConnectorInit();
    assert(context.redis != NULL && context.asyncRedis != NULL);

    redisLibevAttach(EV_DEFAULT, context.asyncRedis);

    // -- publish --
    const char *key = "mytestkey1";
    const char *encodedValue = "abcdef";
    int pubStatus = redisConnectorPublish(context, key, encodedValue);
    assert(pubStatus == 0);

    // -- get --
    const char *value = redisConnectorGet(context, key);
    assert(strcmp(value, encodedValue) == 0);

    // -- subscribe --
    const char *keyList[1] = {key};
    RedisConnectorCallbackData* callbackData = redisConnectorSubscribe(context, keyList, 1, callback, NULL);
    assert(callbackData != NULL);

    int pubStatus2 = redisConnectorPublish(context, key, "12345");
    assert(pubStatus2 == 0);
    assert(strcmp(redisConnectorGet(context, key), "12345") == 0);

    int pubStatus3 = redisConnectorPublish(context, key, "Test message");
    assert(pubStatus3 == 0);
    assert(strcmp(redisConnectorGet(context, key), "Test message") == 0);

    ev_loop(EV_DEFAULT_ 0);
    return 0;
}
