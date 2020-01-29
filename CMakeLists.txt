########################################################################################################################
### UTIL LIBRARY MAIN
########################################################################################################################

cmake_minimum_required(VERSION 3.2)

########################################################################################################################
### PROJECT DESCRIPTION
########################################################################################################################

set(UTIL_PROJECT_NAME        "util")
set(UTIL_PROJECT_DESCRIPTION "A collection of utility classes and functions for C++.")
set(UTIL_AUTHOR_DOMAIN       "https://github.com/sourcechris/util")
set(UTIL_AUTHOR_MAINTAINER   "cg@2601.me")
set(UTIL_VERSION_MAJOR       "0")
set(UTIL_VERSION_MINOR       "0")
set(UTIL_VERSION_PATCH       "1")
set(UTIL_VERSION             "${UTIL_VERSION_MAJOR}.${UTIL_VERSION_MINOR}.${UTIL_VERSION_PATCH}")
set(UTIL_NAME_VERSION        "${UTIL_PROJECT_NAME} v${UTIL_VERSION} (${UTIL_VERSION_REVISION})")

########################################################################################################################
### PROJECT OPTIONS
########################################################################################################################

option(BUILD_SHARED_LIBS     "Build shared instead of static libraries."              OFF)
option(OPTION_SELF_CONTAINED "Create a self-contained install with all dependencies." OFF)
option(OPTION_BUILD_TESTS    "Build tests."                                           ON)
option(OPTION_BUILD_DOCS     "Build documentation."                                   OFF)

########################################################################################################################
### PROJECT SETUP
########################################################################################################################

project(${UTIL_PROJECT_NAME} CXX)

set(UTIL_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(UTIL_INC_DIR ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)

if(OPTION_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
