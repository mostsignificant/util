#include "gtest/gtest.h"
#include "test.hpp"
#include "util/enumerate.hpp"

// clang-format off

TEST(UtilEnumerate, Default) {
//! [enumerate_default]
const std::vector<int> numbers = { 1, 2, 3 };
for (const auto&& [i, number] : util::enumerate(numbers))
    assert(numbers[i] == number);
//! [enumerate_default]
}

// clang-format on