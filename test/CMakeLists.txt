
find_package(hiredis REQUIRED)
#find_package(ev REQUIRED)
find_package(uuid REQUIRED)
find_package(cbor REQUIRED)
include_directories( .. )

#add_executable(testSubscriber testSubscriber1.c)
add_executable(testPublisher testPublisher.c)

#set(libs ${HIREDIS_LIBS} ${EV_LIBS} ${UUID_LIBRARY} ${CBOR_LIBS})
set(libs ${HIREDIS_LIBS} ${UUID_LIBRARY} ${CBOR_LIBS})

#target_link_libraries( testSubscriber csw ${libs})
target_link_libraries( testPublisher csw ${libs})
