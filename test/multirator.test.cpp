#include <vector>

#include "gtest/gtest.h"
#include "test.hpp"
#include "util/multirator.hpp"

TEST(UtilMultirator, ConstIterator) {
    const std::vector numbers = {1, 2, 3};
    const std::vector names = {"Hello", "World", "!"};

    const auto range = util::make_multirator_range(numbers, names);

    auto i = 0;
    for (auto&& [number, name] : range) {
        assert(numbers[i] == number);
        assert(std::strcmp(names[i], name) == 0);
        i++;
    }
}

TEST(UtilMultirator, Iterator) {
    std::vector numbers = {1, 2, 3};
    std::vector chars = {'A', 'B', 'C'};

    auto range = util::make_multirator_range(numbers, chars);

    auto i = 0;
    for (auto& [number, ch] : range) {
        number = number + 1;
        ch = ch + 1;
    }

    const std::vector expected_numbers = {2, 3, 4};
    const std::vector expected_chars = {'B', 'C', 'D'};

    assert(numbers == expected_numbers);
    assert(chars == expected_chars);
}