project(csw LANGUAGES C VERSION 4.0.2)
cmake_minimum_required(VERSION 3.19)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(hiredis REQUIRED)
find_package(zlog REQUIRED)
find_package(cbor REQUIRED)
find_package(uuid REQUIRED)

include_directories( ${ZLOG_INCLUDE_DIRS} ${HIREDIS_INCLUDE_DIRS}  ${CBOR_INCLUDE_DIRS} )

set(sources Event.c RedisConnector.c Parameter.c EventTime.c EventPublisher.c Coords.c)

add_library(${PROJECT_NAME} SHARED ${sources})
target_link_libraries(${PROJECT_NAME} hiredis zlog cbor uuid
        Threads::Threads)

set_target_properties(${PROJECT_NAME} PROPERTIES
        PUBLIC_HEADER csw.h
        SOVERSION ${PROJECT_VERSION})

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
        PUBLIC_HEADER
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/csw
        )


