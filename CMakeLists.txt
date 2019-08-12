cmake_minimum_required(VERSION 3.14)
project(csw_c C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory (csw)
#add_subdirectory (test)
add_subdirectory (examples)

#enable_testing ()
#add_test (NAME MyTest COMMAND Test)
