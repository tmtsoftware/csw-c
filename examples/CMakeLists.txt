
find_package(hiredis REQUIRED)
find_package(ev REQUIRED)
find_package(uuid REQUIRED)
find_package(cbor REQUIRED)
include_directories( .. )

add_executable(testSubscriber testSubscriber1.c)
add_executable(testPublisher1 testPublisher1.c)
add_executable(testPublisher2 testPublisher2.c)
target_link_libraries( testSubscriber csw ${HIREDIS_LIBS} ${EV_LIBS} ${UUID_LIBRARY} ${CBOR_LIBS})
target_link_libraries( testPublisher1 csw ${HIREDIS_LIBS}  ${EV_LIBS} ${UUID_LIBRARY} ${CBOR_LIBS})
target_link_libraries( testPublisher2 csw ${HIREDIS_LIBS}  ${EV_LIBS} ${UUID_LIBRARY} ${CBOR_LIBS})

#${JSON-C_LIBRARIES}

