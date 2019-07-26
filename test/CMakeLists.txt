
find_package(ev REQUIRED)
find_package(hiredis REQUIRED)
include_directories( .. )

#FIND_PATH(LIBEV ev.h
#        HINTS /usr/local /usr/opt/local
#        ENV LIBEV_INCLUDE_DIR)

add_executable(testRedisConnector testRedisConnector.c)
target_link_libraries( testRedisConnector csw ${HIREDIS_LIBS} ${EV_LIBS} )

