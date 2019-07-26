

add_library(csw Event.c Event.h redisConnector.c redisConnector.h Parameter.h EventTime.h)

#find_library( microhttpd REQUIRED )
find_package(hiredis REQUIRED)
include_directories( ${HIREDIS_INCLUDE_DIRS} )

