
set(sources Event.c RedisConnector.c Parameter.c EventTime.c EventPublisher.c)

add_library(csw STATIC ${sources})
add_library(csw-shared SHARED ${sources})

find_package(hiredis REQUIRED)
find_package(ev REQUIRED)
find_package(cbor REQUIRED)
include_directories( ${HIREDIS_INCLUDE_DIRS}  ${EV_INCLUDE_DIRS}  ${CBOR_INCLUDE_DIRS} )

set_target_properties(csw PROPERTIES
        PUBLIC_HEADER csw.h
        VERSION 1.0.0)

set_target_properties(csw-shared PROPERTIES
        PUBLIC_HEADER csw.h
        SOVERSION 1)

include(GNUInstallDirs)

install(TARGETS csw csw-shared
        PUBLIC_HEADER
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/csw
        )

