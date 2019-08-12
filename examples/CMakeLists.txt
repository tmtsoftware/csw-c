
find_package(hiredis REQUIRED)
find_package(ev REQUIRED)
find_package(uuid REQUIRED)
find_package(cbor REQUIRED)
include_directories( .. )

#add_executable(testSubscriber testSubscriber1.c)
add_executable(testPublisher1 testPublisher1.c)
add_executable(testPublisher2 testPublisher2.c)
add_executable(testPublisher3 testPublisher3.c)

set(libs ${HIREDIS_LIBS} ${EV_LIBS} ${UUID_LIBRARY} ${CBOR_LIBS})

#target_link_libraries( testSubscriber csw ${libs})
target_link_libraries( testPublisher1 csw ${libs})
target_link_libraries( testPublisher2 csw ${libs})
target_link_libraries( testPublisher3 csw ${libs})

#${JSON-C_LIBRARIES}

