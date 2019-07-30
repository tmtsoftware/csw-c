# - Find CBOR library
# Once done this will define
#
#  CBOR_FOUND - This defines if we found CBOR
#  CBOR_INCLUDE_DIR - CBOR include directory
#  CBOR_LIBS - CBOR libraries
#  CBOR_DEFINITIONS - Compiler switches required for CBOR


# use pkg-config to get the directories and then use these values
# in the FIND_PATH() and FIND_LIBRARY() calls
#FIND_PACKAGE(PkgConfig)
#PKG_SEARCH_MODULE(PC_LIBCBOR libCBOR)

SET(CBOR_DEFINITIONS ${PC_CBOR_CFLAGS_OTHER})

FIND_PATH(
        CBOR_INCLUDE_DIR
        NAMES "cbor.h"
        PATH_SUFFIXES ""
)

FIND_LIBRARY(CBOR_LIBS NAMES cbor
        HINTS
        ${PC_CBOR_LIBDIR}
        ${PC_CBOR_LIBRARY_DIRS}
        )

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CBOR DEFAULT_MSG CBOR_LIBS CBOR_INCLUDE_DIR)