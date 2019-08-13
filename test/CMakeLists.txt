
#find_package(ev REQUIRED)
find_package(hiredis REQUIRED)
find_package(cbor REQUIRED)
#include_directories( .. ${HIREDIS_INCLUDE_DIRS}  ${EV_INCLUDE_DIRS}  ${CBOR_INCLUDE_DIRS} )
include_directories( .. ${HIREDIS_INCLUDE_DIRS} ${CBOR_INCLUDE_DIRS} )

add_executable(testRedisConnector testRedisConnector.c)
#target_link_libraries( testRedisConnector csw ${HIREDIS_LIBS} ${EV_LIBS} )
target_link_libraries( testRedisConnector csw ${HIREDIS_LIBS} )

include(GNUInstallDirs)
