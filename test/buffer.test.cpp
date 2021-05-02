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

const util::buffer<int, 2> small_stack{1, 2, 3};
assert(small_stack.at(0) == 1);
assert(small_stack.at(1) == 2);
assert(small_stack.at(2) == 3);
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

util::buffer<int, 2> small_stack{1, 2, 3};
assert(small_stack.at(0) == 1);
assert(small_stack.at(1) == 2);
assert(small_stack.at(2) == 3);
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

TEST(UtilBuffer, Front) {
//! [buffer_front]
util::buffer<int> numbers{1, 2, 3};
assert(numbers.front() == 1);
//! [buffer_front]
}

TEST(UtilBuffer, FrontConst) {
//! [buffer_front_const]
const util::buffer<int> numbers{1, 2, 3};
assert(numbers.front() == 1);
//! [buffer_front_const]
}

TEST(UtilBuffer, Back) {
//! [buffer_back]
util::buffer<int> numbers{1, 2, 3};
assert(numbers.back() == 3);
//! [buffer_back]
}

TEST(UtilBuffer, BackConst) {
//! [buffer_back_const]
const util::buffer<int> numbers{1, 2, 3};
assert(numbers.back() == 3);
//! [buffer_back_const]
}

TEST(UtilBuffer, StackData) {
//! [buffer_stack_data]
util::buffer<int> numbers{1, 2, 3};
assert(*numbers.stack_data() == 1);
//! [buffer_stack_data]
}

TEST(UtilBuffer, StackDataConst) {
//! [buffer_stack_data_const]
const util::buffer<int> numbers{1, 2, 3};
assert(*numbers.stack_data() == 1);
//! [buffer_stack_data_const]
}

TEST(UtilBuffer, HeapData) {
//! [buffer_heap_data]
util::buffer<int, 2> numbers{1, 2, 3};
assert(*numbers.heap_data() == 3);
//! [buffer_heap_data]
}

TEST(UtilBuffer, HeapDataConst) {
//! [buffer_heap_data_const]
const util::buffer<int, 2> numbers{1, 2, 3};
assert(*numbers.heap_data() == 3);
//! [buffer_heap_data_const]
}

TEST(UtilBuffer, Begin) {
//! [buffer_begin]
util::buffer<int> numbers{1, 2, 3};
assert(*numbers.begin() == 1);
//! [buffer_begin]

auto it = numbers.begin();
assert(*++it == 2);
assert(*++it == 3);
assert(++it == numbers.end());
}

TEST(UtilBuffer, BeginConst) {
//! [buffer_begin_const]
const util::buffer<int> numbers{1, 2, 3};
assert(*numbers.begin() == 1);
//! [buffer_begin_const]

auto it = numbers.begin();
assert(*++it == 2);
assert(*++it == 3);
assert(++it == numbers.end());
}

TEST(UtilBuffer, Cbegin) {
//! [buffer_cbegin]
util::buffer<int> numbers{1, 2, 3};
assert(*numbers.cbegin() == 1);
//! [buffer_cbegin]

auto it = numbers.cbegin();
assert(*++it == 2);
assert(*++it == 3);
assert(++it == numbers.cend());
}

TEST(UtilBuffer, End) {
//! [buffer_end]
util::buffer<int> numbers{1, 2, 3};
assert(numbers.begin() != numbers.end());
//! [buffer_end]

util::buffer<int> empty;
assert(empty.begin() == empty.end());

auto count = 1;
for (auto number : numbers)
    assert(count++ == number);
}

TEST(UtilBuffer, EndConst) {
//! [buffer_end_const]
const util::buffer<int> numbers{1, 2, 3};
assert(numbers.begin() != numbers.end());
//! [buffer_end_const]

util::buffer<int> empty;
assert(empty.begin() == empty.end());

auto count = 1;
for (auto number : numbers)
    assert(count++ == number);

const util::buffer<int, 2> stack_and_heap{1, 2, 3, 4, 5};
assert(stack_and_heap.begin() != stack_and_heap.end());

count = 1;
for (auto number : stack_and_heap)
    assert(count++ == number);

const util::buffer<int, 5> stack_only{1, 2, 3, 4, 5};
assert(stack_only.begin() != stack_only.end());

count = 1;
for (auto number : stack_only)
    assert(count++ == number);

}

TEST(UtilBuffer, Cend) {
//! [buffer_cend]
util::buffer<int> numbers{1, 2, 3};
assert(numbers.cbegin() != numbers.cend());
//! [buffer_cend]

util::buffer<int> empty;
assert(empty.cbegin() == empty.cend());
}

TEST(UtilBuffer, Empty) {
//! [buffer_empty]
const util::buffer<int> numbers;
assert(numbers.empty());
//! [buffer_empty]

const util::buffer<int> non_empty{1, 2, 3, 4, 5};
assert(!non_empty.empty());
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

TEST(UtilBuffer, MaxSize) {
//! [buffer_max_size]
const util::buffer<int, 32> buf;
assert(buf.max_size() > 32);
//! [buffer_max_size]
}

// clang-format on