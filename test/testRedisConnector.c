////
//// Created by abrighto on 7/25/19.
////
//
//#include <assert.h>
//#include <string.h>
//#include <stdio.h>
//#include <hiredis/adapters/libev.h>
//#include "csw/cswImpl.h"
//
//static void callback(const char *key, const unsigned char *value, size_t len, void *privateData) {
//    printf("Subscribe callback: %s = %s\n", key, value);
//}
//
//int main() {
//    redisContext* redis = cswRedisInit();
//    assert(redis != NULL);
//    redisAsyncContext* asyncRedis = cswRedisAsyncInit();
//    assert(asyncRedis != NULL);
//
//    redisLibevAttach(EV_DEFAULT, asyncRedis);
//
//    // -- publish --
//    const char *key = "mytestkey1";
//    const char *encodedValue = "abcdef";
//    int pubStatus = cswRedisConnectorPublish(redis, key, (unsigned char*)encodedValue, strlen(encodedValue));
//    assert(pubStatus == 0);
//
//    // -- get --
//    CswRedisConnectorGetResult res1 = cswRedisConnectorGet(redis, key);
//    assert(strncmp((char*)res1.data, encodedValue, res1.length) == 0);
//
//    // -- subscribe --
//    const char *keyList[1] = {key};
//    CswRedisConnectorCallbackData* callbackData = cswRedisConnectorSubscribe(asyncRedis, keyList, 1, callback, NULL);
//    assert(callbackData != NULL);
//
//    ev_loop(EV_DEFAULT_ 0);
//
//    free(callbackData);
//    return 0;
//}
