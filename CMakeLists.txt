cmake_minimum_required(VERSION 3.20)
project(csw_c C)
set(CMAKE_C_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
#set( CMAKE_VERBOSE_MAKEFILE on )

add_subdirectory (csw)
add_subdirectory (test)

#enable_testing ()
#add_test (NAME MyTest COMMAND Test)
