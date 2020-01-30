########################################################################################################################
### UTIL LIBRARY TESTS
########################################################################################################################

macro(util_add_test PACKAGE)
    set(TESTNAME ${PROJECT_NAME}-${PACKAGE}-test)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} util gtest gtest_main)
    target_include_directories(${TESTNAME} PUBLIC ${UTIL_INC_DIR})
    add_test(${TESTNAME} ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER test)
endmacro()

set(UTIL_TEST_DIR ${PROJECT_SOURCE_DIR}/test)

########################################################################################################################
### GOOGLETEST DEPENDENCY
########################################################################################################################

add_subdirectory(${PROJECT_SOURCE_DIR}/extern/googletest extern/googletest)

mark_as_advanced(BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
                 gmock_build_tests gtest_build_samples gtest_build_tests
                 gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols)

set_target_properties(gtest      PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)

########################################################################################################################
### UTIL TESTS
########################################################################################################################

util_add_test(endian     ${UTIL_TEST_DIR}/endian.test)
util_add_test(multirator ${UTIL_TEST_DIR}/multirator.test)
util_add_test(scoped     ${UTIL_TEST_DIR}/scoped.test)

