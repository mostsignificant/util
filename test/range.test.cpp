#include "gtest/gtest.h"
#include "util/range.hpp"

TEST(UtilRange, SingleParameter) {
    std::vector<int> numbers;
    for (auto i : util::range(6)) {
        numbers.push_back(i);
    }

    assert(numbers == std::vector<int>({0, 1, 2, 3, 4, 5}));
}

TEST(UtilRange, TwoParameter) {
    std::vector<int> numbers;
    for (auto i : util::range(3, 6)) {
        numbers.push_back(i);
    }

    assert(numbers == std::vector<int>({3, 4, 5}));
}

TEST(UtilRange, ThreeParameter) {
    std::vector<int> numbers;
    for (auto i : util::range(3, 6, 2)) {
        numbers.push_back(i);
    }

    assert(numbers == std::vector<int>({3, 5}));
}