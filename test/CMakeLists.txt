
find_package(hiredis REQUIRED)
#find_package(ev REQUIRED)
find_package(uuid REQUIRED)
find_package(cbor REQUIRED)
include_directories( .. )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/TestAssemblyHandlers.out DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(testPublisher testPublisher.c)

#set(libs ${HIREDIS_LIBS} ${EV_LIBS} ${UUID_LIBRARY} ${CBOR_LIBS})
set(libs ${HIREDIS_LIBS} ${UUID_LIBRARY} ${CBOR_LIBS})

#target_link_libraries( testSubscriber csw ${libs})
target_link_libraries( testPublisher csw ${libs})
