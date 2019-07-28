
find_package(hiredis REQUIRED)
find_package(ev REQUIRED)
include_directories( .. )

add_executable(testSubscriber testSubscriber.c)
target_link_libraries( testSubscriber csw ${HIREDIS_LIBS} ${JSON-C_LIBRARIES})

