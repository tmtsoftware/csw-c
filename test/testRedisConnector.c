//
// Created by abrighto on 7/25/19.
//

#include <csw/redisConnector.h>
#include <assert.h>
#include <string.h>
#include <zconf.h>

#include <stdio.h>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
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
    int subStatus = redisConnectorSubscribeCallback(context, keyList, 1, callback, NULL);
    assert(subStatus == 0);

    int pubStatus2 = redisConnectorPublish(context, key, "12345");
    assert(pubStatus2 == 0);
    assert(strcmp(redisConnectorGet(context, key), "12345") == 0);

    int pubStatus3 = redisConnectorPublish(context, key, "Test message");
    assert(pubStatus3 == 0);
    assert(strcmp(redisConnectorGet(context, key), "Test message") == 0);

    ev_loop(EV_DEFAULT_ 0);
    return 0;
}
