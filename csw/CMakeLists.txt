project(csw LANGUAGES C VERSION 0.1)
cmake_minimum_required(VERSION 3.19)
set(CMAKE_C_STANDARD 11)

find_package(hiredis REQUIRED)
find_package(cbor REQUIRED)
find_package(uuid REQUIRED)

include_directories( ${HIREDIS_INCLUDE_DIRS}  ${CBOR_INCLUDE_DIRS} )

set(sources Event.c RedisConnector.c Parameter.c EventTime.c EventPublisher.c Coords.c)

add_library(${PROJECT_NAME} SHARED ${sources})
target_link_libraries(${PROJECT_NAME} hiredis cbor uuid)

set_target_properties(${PROJECT_NAME} PROPERTIES
        PUBLIC_HEADER csw.h
        SOVERSION 1)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
        PUBLIC_HEADER
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/csw
        )


