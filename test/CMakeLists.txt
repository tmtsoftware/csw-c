
find_package(ev REQUIRED)
find_package(hiredis REQUIRED)
find_package(cbor REQUIRED)
include_directories( .. )

add_executable(testRedisConnector testRedisConnector.c)
target_link_libraries( testRedisConnector csw ${HIREDIS_LIBS} ${EV_LIBS} )

