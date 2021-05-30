#include "gtest/gtest.h"
#include "util/ignore_unused.hpp"

// clang-format off

TEST(UtilIgnoreUnused, Function) {
//! [ignore_unused_function]
void function(int number, const std::string& name) {
    util::ignore_unused(number, name);
    // ...
}
//! [ignore_unused_function]
}

// clang-format on