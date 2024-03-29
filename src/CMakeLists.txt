########################################################################################################################
### UTIL LIBRARY
########################################################################################################################

set(UTIL_TARGET_NAME util)

set(UTIL_INC_FILES
        ${UTIL_INC_DIR}/util/array.hpp
        ${UTIL_INC_DIR}/util/assert.hpp
        ${UTIL_INC_DIR}/util/buffer.hpp
        ${UTIL_INC_DIR}/util/enumerate.hpp
        ${UTIL_INC_DIR}/util/exception.hpp
        ${UTIL_INC_DIR}/util/flags.hpp
        ${UTIL_INC_DIR}/util/ignore_unused.hpp
        ${UTIL_INC_DIR}/util/multirator.hpp
        ${UTIL_INC_DIR}/util/non_copyable.hpp
        ${UTIL_INC_DIR}/util/non_moveable.hpp
        ${UTIL_INC_DIR}/util/ring_buffer.hpp
        ${UTIL_INC_DIR}/util/scoped.hpp
        ${UTIL_INC_DIR}/util/shared.hpp
        ${UTIL_INC_DIR}/util/sorted.hpp
        ${UTIL_INC_DIR}/util/var.hpp
)

set(UTIL_SRC_FILES
        ${UTIL_SRC_DIR}/array.cpp
        ${UTIL_SRC_DIR}/assert.cpp
        ${UTIL_SRC_DIR}/buffer.cpp
        ${UTIL_SRC_DIR}/color.cpp
        ${UTIL_SRC_DIR}/enumerate.cpp
        ${UTIL_SRC_DIR}/exception.cpp
        ${UTIL_SRC_DIR}/flags.cpp
        ${UTIL_SRC_DIR}/ignore_unused.cpp
        ${UTIL_SRC_DIR}/multirator.cpp
        ${UTIL_SRC_DIR}/non_copyable.cpp
        ${UTIL_SRC_DIR}/non_moveable.cpp
        ${UTIL_SRC_DIR}/range.cpp
        ${UTIL_SRC_DIR}/ring_buffer.cpp
        ${UTIL_SRC_DIR}/scoped.cpp
        ${UTIL_SRC_DIR}/shared.cpp
        ${UTIL_SRC_DIR}/sorted.cpp
        ${UTIL_SRC_DIR}/var.cpp
)

add_library(util STATIC
        ${UTIL_INC_FILES}
        ${UTIL_SRC_FILES}
)

target_compile_features(${UTIL_TARGET_NAME} PRIVATE
        cxx_std_17
)

target_compile_definitions(${UTIL_TARGET_NAME} PUBLIC 
        ${UTIL_ASSERT}
)

target_include_directories(${UTIL_TARGET_NAME} PUBLIC
        ${UTIL_INC_DIR}
)
