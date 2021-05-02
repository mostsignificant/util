#include "gtest/gtest.h"
#include "test.hpp"
#include "util/buffer.hpp"

// clang-format off

TEST(UtilBuffer, CtorDefault) {
//! [buffer_ctor_default]
const util::buffer<int> numbers;
assert(numbers.size() == 0);
//! [buffer_ctor_default]
}

TEST(UtilBuffer, CtorInitializerList) {
//! [buffer_ctor_initializer_list]
const util::buffer<int> numbers{1, 2, 3};
//! [buffer_ctor_initializer_list]

assert(numbers.size() == 3);

assert(numbers.at(0) == 1);
assert(numbers.at(1) == 2);
assert(numbers.at(2) == 3);

}

TEST(UtilBuffer, AtConst) {
//! [buffer_at_const]
const util::buffer<int> numbers{1, 2, 3};
assert(numbers.at(2) == 3);
//! [buffer_at_const]

assert(numbers.at(0) == 1);
assert(numbers.at(1) == 2);

try {
    assert(numbers.at(3));
}
catch (const std::out_of_range& x) {
    assert(true);
}
}

TEST(UtilBuffer, At) {
//! [buffer_at]
util::buffer<int> numbers{1, 2, 3};
assert(numbers.at(2) == 3);
//! [buffer_at]

assert(numbers.at(0) == 1);
assert(numbers.at(1) == 2);

try {
    assert(numbers.at(3));
}
catch (const std::out_of_range& x) {
    assert(true);
}
}

TEST(UtilBuffer, OperatorSquareBrackets) {
//! [buffer_operator_square_brackets]
util::buffer<int> numbers{1, 2, 3};
assert(numbers[2] == 3);
//! [buffer_operator_square_brackets]

assert(numbers[0] == 1);
assert(numbers[1] == 2);
}

TEST(UtilBuffer, OperatorSquareBracketsConst) {
//! [buffer_operator_square_brackets_const]
const util::buffer<int> numbers{1, 2, 3};
assert(numbers[2] == 3);
//! [buffer_operator_square_brackets_const]

assert(numbers[0] == 1);
assert(numbers[1] == 2);
}

TEST(UtilBuffer, Size) {
//! [buffer_size]
const util::buffer<int> numbers{1, 2, 3, 4, 5};
assert(numbers.size() == 5);
//! [buffer_size]

const util::buffer<int> empty;
assert(empty.size() == 0);

const util::buffer<int, 2> stack_and_heap{1, 2, 3, 4, 5};
assert(stack_and_heap.size() == 5);
}

// clang-format on