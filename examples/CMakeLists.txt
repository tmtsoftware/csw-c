
find_package(hiredis REQUIRED)
find_package(ev REQUIRED)
find_package(cbor REQUIRED)
include_directories( .. )

add_executable(testSubscriber testSubscriber.c)
add_executable(testPublisher testPublisher.c)
target_link_libraries( testSubscriber csw ${HIREDIS_LIBS} ${EV_LIBS} ${CBOR_LIBS})
target_link_libraries( testPublisher csw ${HIREDIS_LIBS}  ${EV_LIBS} ${CBOR_LIBS})

#${JSON-C_LIBRARIES}

