########################################################################################################################
### UTIL LIBRARY TESTS
########################################################################################################################

project(${UTIL_PROJECT_NAME}-test CXX)

macro(util_add_test TESTBASENAME)
    set(TESTNAME ${UTIL_PROJECT_NAME}-test-${TESTBASENAME})
    add_executable(${TESTNAME} ${ARGN})

    target_compile_features(${TESTNAME} PUBLIC cxx_std_17)
    target_include_directories(${TESTNAME} PRIVATE ${UTIL_INC_DIR})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)

    gtest_discover_tests(${TESTNAME}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )

    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

########################################################################################################################
### GOOGLETEST DEPENDENCY
########################################################################################################################

add_subdirectory(${CMAKE_SOURCE_DIR}/extern/googletest extern/googletest)

mark_as_advanced(BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
                 gmock_build_tests gtest_build_samples gtest_build_tests
                 gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

########################################################################################################################
### UTIL TESTS
########################################################################################################################

set(UTIL_TEST_DIR ${CMAKE_SOURCE_DIR}/test)

util_add_test(array         ${UTIL_TEST_DIR}/array.test.cpp)
util_add_test(flags         ${UTIL_TEST_DIR}/flags.test.cpp)
util_add_test(multirator    ${UTIL_TEST_DIR}/multirator.test.cpp)
util_add_test(non_copyable  ${UTIL_TEST_DIR}/non_copyable.test.cpp)
util_add_test(non_moveable  ${UTIL_TEST_DIR}/non_moveable.test.cpp)
util_add_test(ring_buffer   ${UTIL_TEST_DIR}/ring_buffer.test.cpp)
util_add_test(scoped        ${UTIL_TEST_DIR}/scoped.test.cpp)
util_add_test(shared        ${UTIL_TEST_DIR}/shared.test.cpp)
util_add_test(sorted_vector ${UTIL_TEST_DIR}/sorted_vector.test.cpp)
util_add_test(var           ${UTIL_TEST_DIR}/var.test.cpp)
