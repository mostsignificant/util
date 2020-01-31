########################################################################################################################
### UTIL LIBRARY
########################################################################################################################

set( CMAKE_VERBOSE_MAKEFILE on )

set(UTIL_TARGET_NAME util)

set(UTIL_INC_FILES
        ${UTIL_INC_DIR}/util/endian
        ${UTIL_INC_DIR}/util/multirator
        ${UTIL_INC_DIR}/util/scoped
        )

set(UTIL_SRC_FILES
        ${UTIL_SRC_DIR}/endian
        ${UTIL_SRC_DIR}/multirator
        ${UTIL_SRC_DIR}/scoped
        )


add_library(util STATIC
        ${UTIL_INC_FILES}
        ${UTIL_SRC_FILES}
        )

target_include_directories(${UTIL_TARGET_NAME} PUBLIC
        ${UTIL_INC_DIR})

