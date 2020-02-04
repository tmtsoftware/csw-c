////
//// Created by abrighto on 7/24/19.
////
//
//#include <assert.h>
//#include <string.h>
//#include <stdio.h>
//#include <hiredis/adapters/libev.h>
//
//#include "csw/cswImpl.h"
//
//// XXX TODO: Event Subscribe API is not implemented yet. This is using Redis directly.
//// XXX TODO: Still need to add support for decoding CBOR to Event.
//
//static void callback(const char *key, const unsigned char *value, size_t len, void *privateData) {
//    printf("Subscribe callback: %s = %d bytes\n", key, (int)len);
//
//    /* Assuming `buffer` contains `length` bytes of input data */
//    struct cbor_load_result result;
//    cbor_item_t* item = cbor_load(value, len, &result);
//
//    if (result.error.code != CBOR_ERR_NONE) {
//        printf(
//                "There was an error while reading the input near byte %zu (read %zu "
//                "bytes in total): ",
//                result.error.position, result.read);
//        switch (result.error.code) {
//            case CBOR_ERR_MALFORMATED: {
//                printf("Malformed data\n");
//                break;
//            }
//            case CBOR_ERR_MEMERROR: {
//                printf("Memory error -- perhaps the input is too large?\n");
//                break;
//            }
//            case CBOR_ERR_NODATA: {
//                printf("The input is empty\n");
//                break;
//            }
//            case CBOR_ERR_NOTENOUGHDATA: {
//                printf("Data seem to be missing -- is the input complete?\n");
//                break;
//            }
//            case CBOR_ERR_SYNTAXERROR: {
//                printf(
//                        "Syntactically malformed data -- see "
//                        "http://tools.ietf.org/html/rfc7049\n");
//                break;
//            }
//            case CBOR_ERR_NONE: {
//                // GCC's cheap dataflow analysis gag
//                break;
//            }
//        }
//        exit(1);
//    }
//
//    /* Pretty-print the result */
//    cbor_describe(item, stdout);
//    fflush(stdout);
//    /* Deallocate the result */
//    cbor_decref(&item);
//
//
//}
//
//// XXX TODO: TEMP: until event subscriber code is implemented
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
//    const char *key = "CSW.testassembly.myAssemblyEvent";
//
//    // -- get --
//    CswRedisConnectorGetResult getResult = cswRedisConnectorGet(redis, key);
//    callback(key, getResult.data, getResult.length, NULL);
//
//    // -- subscribe --
//    const char *keyList[1] = {key};
//    CswRedisConnectorCallbackData* callbackData = cswRedisConnectorSubscribe(asyncRedis, keyList, 1, callback, NULL);
//    assert(callbackData != NULL);
//
//    ev_loop(EV_DEFAULT_ 0);
//    return 0;
//}
