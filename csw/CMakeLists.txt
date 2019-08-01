
add_library(csw Event.c Event.h RedisConnector.c RedisConnector.h Parameter.h EventTime.h Parameter.c EventTime.c Coords.h EventPublisher.c EventPublisher.h)

#find_library( microhttpd REQUIRED )
find_package(hiredis REQUIRED)
find_package(ev REQUIRED)
find_package(cbor REQUIRED)
include_directories( ${HIREDIS_INCLUDE_DIRS}  ${EV_INCLUDE_DIRS}  ${CBOR_INCLUDE_DIRS} )

#find_package(json-c REQUIRED)
#include_directories( ${JSON-C_INCLUDE_DIRS} )

