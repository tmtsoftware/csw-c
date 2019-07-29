

add_library(csw Event.c Event.h RedisConnector.c RedisConnector.h Parameter.h EventTime.h Parameter.c EventTime.c Coords.h)

#find_library( microhttpd REQUIRED )
find_package(hiredis REQUIRED)
include_directories( ${HIREDIS_INCLUDE_DIRS} )

find_package(json-c REQUIRED)
include_directories( ${JSON-C_INCLUDE_DIRS} )

