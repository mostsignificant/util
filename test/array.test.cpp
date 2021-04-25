#include "gtest/gtest.h"
#include "test.hpp"
#include "util/array.hpp"

// clang-format off

TEST(UtilArray, Ctor) {
//! [array_ctor]
constexpr const util::array<int, 3> numbers{1, 2, 3};
//! [array_ctor]
}

// clang-format on