#include "gtest/gtest.h"
#include "test.hpp"
#include "util/array.hpp"

// clang-format off

TEST(UtilArray, Ctor) {
//! [array_ctor]
constexpr const util::array<int, 3> numbers{1, 2, 3};
//! [array_ctor]
}

TEST(UtilArray, At) {
//! [array_at]
util::array<int, 3> numbers{1, 2, 3};
assert(numbers.at(0) == 1);
//! [array_at]

assert(numbers.at(1) == 2);
assert(numbers.at(2) == 3);
}

TEST(UtilArray, ConstAt) {
//! [array_const_at]
constexpr const util::array<int, 3> numbers{1, 2, 3};
assert(numbers.at(0) == 1);
//! [array_const_at]

assert(numbers.at(1) == 2);
assert(numbers.at(2) == 3);
}

TEST(UtilArray, OperatorSquareBrackets) {
//! [array_operator_square_brackets]
util::array<int, 3> numbers{1, 2, 3};
assert(numbers[2] == 3);
//! [array_operator_square_brackets]

assert(numbers[0] == 1);
assert(numbers[1] == 2);
}

TEST(UtilArray, OperatorSquareBracketsConst) {
//! [array_operator_square_brackets_const]
const util::array<int, 3> numbers{1, 2, 3};
assert(numbers[2] == 3);
//! [array_operator_square_brackets_const]

assert(numbers[0] == 1);
assert(numbers[1] == 2);
}

TEST(UtilArray, Data) {
//! [array_data]
util::array<int, 3> numbers{1, 2, 3};
assert(*numbers.data() == 1);
//! [array_data]
}

TEST(UtilArray, ConstData) {
//! [array_const_data]
constexpr const util::array<int, 3> numbers{1, 2, 3};
assert(*numbers.data() == 1);
//! [array_const_data]
}

// clang-format on