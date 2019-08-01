//
// Created by abrighto on 7/24/19.
//

#include "csw/Event.h"
#include <csw/RedisConnector.h>
#include <assert.h>
#include <string.h>

#include <stdio.h>
#include <hiredis/adapters/libev.h>

static void callback(const char *key, const unsigned char *value, size_t len, void *privateData) {
//    printf("Subscribe callback: %s = %s\n", key, value);

    printf("Subscribe callback: %s = %d bytes\n", key, (int)len);

    /* Assuming `buffer` contains `length` bytes of input data */
    struct cbor_load_result result;
    cbor_item_t* item = cbor_load(value, len, &result);

    if (result.error.code != CBOR_ERR_NONE) {
        printf(
                "There was an error while reading the input near byte %zu (read %zu "
                "bytes in total): ",
                result.error.position, result.read);
        switch (result.error.code) {
            case CBOR_ERR_MALFORMATED: {
                printf("Malformed data\n");
                break;
            }
            case CBOR_ERR_MEMERROR: {
                printf("Memory error -- perhaps the input is too large?\n");
                break;
            }
            case CBOR_ERR_NODATA: {
                printf("The input is empty\n");
                break;
            }
            case CBOR_ERR_NOTENOUGHDATA: {
                printf("Data seem to be missing -- is the input complete?\n");
                break;
            }
            case CBOR_ERR_SYNTAXERROR: {
                printf(
                        "Syntactically malformed data -- see "
                        "http://tools.ietf.org/html/rfc7049\n");
                break;
            }
            case CBOR_ERR_NONE: {
                // GCC's cheap dataflow analysis gag
                break;
            }
        }
//        exit(1);
    }

    /* Pretty-print the result */
    cbor_describe(item, stdout);
    fflush(stdout);
    /* Deallocate the result */
    cbor_decref(&item);


}

// XXX TODO: TEMP

int main() {
    CswRedisConnectorContext context = cswRedisConnectorInit();
    assert(context.redis != NULL && context.asyncRedis != NULL);

    redisLibevAttach(EV_DEFAULT, context.asyncRedis);

    // -- publish --
    const char *key = "test.assembly.myAssemblyEvent";

    // -- subscribe --
    const char *keyList[1] = {key};
    CswRedisConnectorCallbackData* callbackData = cswRedisConnectorSubscribe(context, keyList, 1, callback, NULL);
    assert(callbackData != NULL);

    ev_loop(EV_DEFAULT_ 0);
    return 0;
}
