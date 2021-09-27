# Try to find zlog
# Once done, this will define
#
# ZLOG_FOUND        - system has zlog
# ZLOG_INCLUDE_DIRS - zlog include directories
# ZLOG_LIBS    - libraries need to use zlog

if(ZLOG_INCLUDE_DIRS AND ZLOG_LIBS)
    set(ZLOG_FIND_QUIETLY TRUE)
else()
    find_path(
            ZLOG_INCLUDE_DIR
            NAMES zlog.h
            HINTS ${ZLOG_ROOT_DIR}
            PATH_SUFFIXES include)

    find_library(
            ZLOG_LIBRARY
            NAMES zlog
            HINTS ${ZLOG_ROOT_DIR}
            PATH_SUFFIXES ${CMAKE_INSTALL_LIBDIR})

    set(ZLOG_INCLUDE_DIRS ${ZLOG_INCLUDE_DIR})
    set(ZLOG_LIBS ${ZLOG_LIBRARY})

    include (FindPackageHandleStandardArgs)
    find_package_handle_standard_args(
            zlog DEFAULT_MSG ZLOG_LIBRARY ZLOG_INCLUDE_DIR)

    mark_as_advanced(ZLOG_LIBRARY ZLOG_INCLUDE_DIR)
endif()
