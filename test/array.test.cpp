#include "gtest/gtest.h"
#include "test.hpp"
#include "util/array.hpp"

// clang-format off

TEST(UtilArray, Ctor) {
//! [array_ctor]
constexpr const util::array<int, 3> numbers{1, 2, 3};
//! [array_ctor]

constexpr const util::array<int, 0> empty{};
}

TEST(UtilArray, At) {
//! [array_at]
util::array<int, 3> numbers{1, 2, 3};
assert(numbers.at(0) == 1);
//! [array_at]

assert(numbers.at(1) == 2);
assert(numbers.at(2) == 3);

try {
    util::array<int, 0> empty{};
    auto&& val = empty.at(666);
} 
catch (const util::out_of_range& oor) {
    assert(true);
}
}

TEST(UtilArray, ConstAt) {
//! [array_const_at]
constexpr const util::array<int, 3> numbers{1, 2, 3};
assert(numbers.at(0) == 1);
//! [array_const_at]

assert(numbers.at(1) == 2);
assert(numbers.at(2) == 3);

try {
    constexpr const util::array<int, 0> empty{};
    auto&& val = empty.at(666);
} 
catch (const util::out_of_range& oor) {
    assert(true);
}
}

TEST(UtilArray, OperatorSquareBrackets) {
//! [array_operator_square_brackets]
util::array<int, 3> numbers{1, 2, 3};
assert(numbers[2] == 3);
//! [array_operator_square_brackets]

assert(numbers[0] == 1);
assert(numbers[1] == 2);

#ifdef UTIL_ASSERT
try {
    const auto x = numbers[3];
} catch (const util::assertion& a) {
    assert(true);
}
#endif

try {
    util::array<int, 0> empty{};
    auto&& val = empty[666];
} 
catch (const util::out_of_range& oor) {
    assert(true);
}
}

TEST(UtilArray, OperatorSquareBracketsConst) {
//! [array_operator_square_brackets_const]
constexpr const util::array<int, 3> numbers{1, 2, 3};
assert(numbers[2] == 3);
//! [array_operator_square_brackets_const]

assert(numbers[0] == 1);
assert(numbers[1] == 2);

#ifdef UTIL_ASSERT
try {
    const auto x = numbers[3];
} catch (const util::assertion& a) {
    assert(true);
}
#endif

try {
    constexpr const util::array<int, 0> empty{};
    auto&& val = empty[666];
} 
catch (const util::out_of_range& oor) {
    assert(true);
}
}

TEST(UtilArray, Front) {
//! [array_front]
util::array<int, 3> numbers{1, 2, 3};
assert(numbers.front() == 1);
//! [array_front]

try {
    constexpr const util::array<int, 0> empty{};
    auto&& val = empty.front();
} 
catch (const util::out_of_range& oor) {
    assert(true);
}
}

TEST(UtilArray, FrontConst) {
//! [array_front_const]
constexpr const util::array<int, 3> numbers{1, 2, 3};
assert(numbers.front() == 1);
//! [array_front_const]

try {
    constexpr const util::array<int, 0> empty{};
    auto&& val = empty.front();
} 
catch (const util::out_of_range& oor) {
    assert(true);
}
}

TEST(UtilArray, Back) {
//! [array_back]
util::array<int, 3> numbers{1, 2, 3};
assert(numbers.back() == 3);
//! [array_back]

try {
    constexpr const util::array<int, 0> empty{};
    auto&& val = empty.back();
} 
catch (const util::out_of_range& oor) {
    assert(true);
}
}

TEST(UtilArray, BackConst) {
//! [array_back_const]
constexpr const util::array<int, 3> numbers{1, 2, 3};
assert(numbers.back() == 3);
//! [array_back_const]

try {
    constexpr const util::array<int, 0> empty{};
    auto&& val = empty.back();
} 
catch (const util::out_of_range& oor) {
    assert(true);
}
}

TEST(UtilArray, Data) {
//! [array_data]
util::array<int, 3> numbers{1, 2, 3};
assert(*numbers.data() == 1);
//! [array_data]

util::array<int, 0> empty{};
assert(empty.data());
}

TEST(UtilArray, ConstData) {
//! [array_const_data]
constexpr const util::array<int, 3> numbers{1, 2, 3};
assert(*numbers.data() == 1);
//! [array_const_data]

constexpr const util::array<int, 0> empty{};
assert(empty.data());
}

TEST(UtilArray, Begin) {
//! [array_begin]
util::array<int, 3> numbers{1, 2, 3};
assert(*numbers.begin() == 1);
//! [array_begin]

util::array<int, 0> empty{};
assert(empty.begin() == empty.end());
}

TEST(UtilArray, BeginConst) {
//! [array_begin]
const util::array<int, 3> numbers{1, 2, 3};
assert(*numbers.begin() == 1);
//! [array_begin]

const util::array<int, 0> empty{};
assert(empty.begin() == empty.end());
}

TEST(UtilArray, Cbegin) {
//! [array_cbegin]
util::array<int, 3> numbers{1, 2, 3};
assert(*numbers.cbegin() == 1);
//! [array_cbegin]

util::array<int, 0> empty{};
assert(empty.cbegin() == empty.cend());
}

TEST(UtilArray, End) {
//! [array_end]
util::array<int, 3> numbers{1, 2, 3};
assert(numbers.begin() + numbers.size() == numbers.end());
//! [array_end]
}

TEST(UtilArray, EndConst) {
//! [array_end_const]
constexpr const util::array<int, 3> numbers{1, 2, 3};
assert(numbers.begin() + numbers.size() == numbers.end());
//! [array_end_const]
}

TEST(UtilArray, Cend) {
//! [array_cend]
util::array<int, 3> numbers{1, 2, 3};
assert(numbers.cbegin() + numbers.size() == numbers.cend());
//! [array_cend]
}

TEST(UtilArray, Rbegin) {
//! [array_rbegin]
util::array<int, 3> numbers{1, 2, 3};
assert(*numbers.rbegin() == 3);
//! [array_rbegin]

util::array<int, 0> empty{};
assert(empty.rbegin() == empty.rend());
}

TEST(UtilArray, RbeginConst) {
//! [array_rbegin_const]
constexpr const util::array<int, 3> numbers{1, 2, 3};
assert(*numbers.rbegin() == 3);
//! [array_rbegin_const]

constexpr const util::array<int, 0> empty{};
assert(empty.rbegin() == empty.rend());
}

TEST(UtilArray, Crbegin) {
//! [array_crbegin]
util::array<int, 3> numbers{1, 2, 3};
assert(*numbers.crbegin() == 3);
//! [array_crbegin]

util::array<int, 0> empty{};
assert(empty.crbegin() == empty.crend());
}

TEST(UtilArray, Empty) {
//! [array_empty]
util::array<int, 3> numbers{1, 2, 3};
assert(!numbers.empty());

util::array<int, 0> null;
assert(null.empty());
//! [array_empty]
}

TEST(UtilArray, Size) {
//! [array_size]
util::array<int, 3> numbers{1, 2, 3};
assert(numbers.size() == 3);

util::array<int, 0> empty;
assert(empty.size() == 0);
//! [array_size]
}

TEST(UtilArray, MaxSize) {
//! [array_max_size]
util::array<int, 3> numbers{1, 2, 3};
assert(numbers.max_size() == 3);

util::array<int, 0> empty;
assert(empty.max_size() == 0);
//! [array_max_size]
}

TEST(UtilArray, Fill) {
//! [array_fill]
util::array<int, 3> numbers;
numbers.fill(0);
assert(numbers.at(0) == 0);
assert(numbers.at(1) == 0);
assert(numbers.at(2) == 0);
//! [array_fill]

util::array<int, 0> empty{};
empty.fill(99);
}

TEST(UtilArray, Swap) {
//! [array_swap]
util::array<int, 3> asc{ 1, 2, 3};
util::array<int, 3> desc{ 3, 2, 1};
asc.swap(desc);
assert(asc.at(0) == 3);
assert(asc.at(1) == 2);
assert(asc.at(2) == 1);
//! [array_swap]

util::array<int, 0> empty{};
empty.swap(empty);
}

// clang-format on