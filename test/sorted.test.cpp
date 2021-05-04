#include <string>

#include "gtest/gtest.h"
#include "test.hpp"
#include "util/sorted.hpp"

TEST(UtilSorted, CtorDefault) {
    //! [sorted_ctor_default]
    util::sorted_vector<int> numbers;
    //! [sorted_ctor_default]

    util::sorted_forward_list<int> fwd_list;
    util::sorted_list<int> list;
}

TEST(UtilSorted, CtorContainer) {
    //! [sorted_ctor_container]
    std::vector<int> unsorted = {3, 1, 2};
    const util::sorted_vector<int> numbers(unsorted);
    assert(numbers.at(0) == 1);
    assert(numbers.at(1) == 2);
    assert(numbers.at(2) == 3);
    //! [sorted_ctor_container]

    const util::sorted_forward_list<int> fwd_list(unsorted);
    assert(fwd_list.at(0) == 1);
    assert(fwd_list.at(1) == 2);
    assert(fwd_list.at(2) == 3);

    const util::sorted_list<int> list(unsorted);
    assert(list.at(0) == 1);
    assert(list.at(1) == 2);
    assert(list.at(2) == 3);
}

TEST(UtilSorted, CtorIter) {
    //! [sorted_ctor_iter]
    auto unsorted = {3, 1, 2};
    const util::sorted_vector<int> numbers(std::begin(unsorted), std::end(unsorted));
    assert(numbers.at(0) == 1);
    assert(numbers.at(1) == 2);
    assert(numbers.at(2) == 3);
    //! [sorted_ctor_iter]

    const util::sorted_forward_list<int> fwd_list(std::begin(unsorted), std::end(unsorted));
    assert(fwd_list.at(0) == 1);
    assert(fwd_list.at(1) == 2);
    assert(fwd_list.at(2) == 3);

    const util::sorted_list<int> list(std::begin(unsorted), std::end(unsorted));
    assert(list.at(0) == 1);
    assert(list.at(1) == 2);
    assert(list.at(2) == 3);
}

TEST(UtilSorted, CtorIList) {
    //! [sorted_ctor_ilist]
    const util::sorted_vector<int> numbers = {3, 1, 2};
    assert(numbers.at(0) == 1);
    assert(numbers.at(1) == 2);
    assert(numbers.at(2) == 3);
    //! [sorted_ctor_ilist]

    const util::sorted_forward_list<int> fwd_list = {3, 1, 2};
    assert(fwd_list.at(0) == 1);
    assert(fwd_list.at(1) == 2);
    assert(fwd_list.at(2) == 3);

    const util::sorted_list<int> list = {3, 1, 2};
    assert(list.at(0) == 1);
    assert(list.at(1) == 2);
    assert(list.at(2) == 3);
}

TEST(UtilSorted, At) {
    //! [sorted_at]
    const util::sorted_vector<int> numbers = {3, 1, 2};
    assert(numbers.at(0) == 1);
    assert(numbers.at(1) == 2);
    assert(numbers.at(2) == 3);
    //! [sorted_at]

    try {
        numbers.at(4);
    } catch (const std::out_of_range& x) {
        assert(true);
    }

    const util::sorted_forward_list<int> fwd_list = {3, 1, 2};
    assert(fwd_list.at(0) == 1);
    assert(fwd_list.at(1) == 2);
    assert(fwd_list.at(2) == 3);

    try {
        fwd_list.at(4);
    } catch (const std::out_of_range& x) {
        assert(true);
    }

    const util::sorted_list<int> list = {3, 1, 2};
    assert(list.at(0) == 1);
    assert(list.at(1) == 2);
    assert(list.at(2) == 3);

    try {
        list.at(4);
    } catch (const std::out_of_range& x) {
        assert(true);
    }
}

TEST(UtilSorted, OperatorSquareBrackets) {
    //! [sorted_operator_square_brackets]
    const util::sorted_vector<int> numbers = {3, 1, 2};
    assert(numbers[0] == 1);
    assert(numbers[1] == 2);
    assert(numbers[2] == 3);
    //! [sorted_operator_square_brackets]

#ifdef UTIL_ASSERT
    try {
        const auto x = numbers[3];
    } catch (const util::assertion& a) {
        assert(true);
    }
#endif

    const util::sorted_forward_list<int> fwd_list = {3, 1, 2};
    assert(fwd_list[0] == 1);
    assert(fwd_list[1] == 2);
    assert(fwd_list[2] == 3);

#ifdef UTIL_ASSERT
    try {
        const auto x = fwd_list[3];
    } catch (const util::assertion& a) {
        assert(true);
    }
#endif

    const util::sorted_list<int> list = {3, 1, 2};
    assert(list[0] == 1);
    assert(list[1] == 2);
    assert(list[2] == 3);

#ifdef UTIL_ASSERT
    try {
        const auto x = list[3];
    } catch (const util::assertion& a) {
        assert(true);
    }
#endif
}

TEST(UtilSorted, Size) {
    //! [sorted_size]
    util::sorted_vector<std::string> names;
    assert(names.size() == 0);
    names.insert("Chris");
    names.insert("Dora");
    assert(names.size() == 2);
    //! [sorted_size]

    const util::sorted_forward_list<int> fwd_list = {3, 1, 2};
    assert(fwd_list.size() == 3);

    const util::sorted_list<int> list = {3, 1, 2};
    assert(list.size() == 3);
}

TEST(UtilSorted, Capacity) {
    //! [sorted_capacity]
    util::sorted_vector<std::string> cities;
    assert(cities.capacity() == 0);
    cities.insert("Madrid");
    cities.insert("Prague");
    cities.insert("Vienna");
    assert(cities.capacity() >= 3);
    //! [sorted_capacity]

    const util::sorted_forward_list<int> fwd_list = {3, 1, 2};
    assert(fwd_list.capacity() >= 3);

    const util::sorted_list<int> list = {3, 1, 2};
    assert(list.capacity() >= 3);
}

TEST(UtilSorted, Clear) {
    //! [sorted_clear]
    util::sorted_vector<double> doubles({1, 2, 3});
    const auto cap = doubles.capacity();
    doubles.clear();
    assert(doubles.size() == 0);
    assert(doubles.capacity() == cap);
    //! [sorted_clear]

    util::sorted_forward_list<int> fwd_list = {3, 1, 2};
    fwd_list.clear();
    assert(fwd_list.size() == 0);

    util::sorted_list<int> list = {3, 1, 2};
    list.clear();
    assert(list.size() == 0);
}

TEST(UtilSorted, Insert) {
    //! [sorted_insert]
    util::sorted_vector<int> numbers({3, 1, 2});
    auto it = numbers.insert(0);
    assert(*it == 0);
    assert(numbers.at(0) == 0);
    assert(numbers.at(1) == 1);
    assert(numbers.at(2) == 2);
    assert(numbers.at(3) == 3);
    //! [sorted_insert]

    // sorted_forward_list insert at begin
    {
        util::sorted_forward_list<int> fwd_list({3, 1, 2});
        auto fwd_it = fwd_list.insert(0);
        assert(*fwd_it == 0);
        assert(fwd_list.at(0) == 0);
        assert(fwd_list.at(1) == 1);
        assert(fwd_list.at(2) == 2);
        assert(fwd_list.at(3) == 3);
    }

    // sorted_forward_list insert at end
    {
        util::sorted_forward_list<int> fwd_list({3, 1, 2});
        auto fwd_it = fwd_list.insert(4);
        assert(*fwd_it == 4);
        assert(fwd_list.at(0) == 1);
        assert(fwd_list.at(1) == 2);
        assert(fwd_list.at(2) == 3);
        assert(fwd_list.at(3) == 4);
    }

    // sorted_forward_list insert at mid
    {
        util::sorted_forward_list<int> fwd_list({4, 1, 2});
        auto fwd_it = fwd_list.insert(3);
        assert(*fwd_it == 3);
        assert(fwd_list.at(0) == 1);
        assert(fwd_list.at(1) == 2);
        assert(fwd_list.at(2) == 3);
        assert(fwd_list.at(3) == 4);
    }

    util::sorted_list<int> list({3, 1, 2});
    list.insert(0);
    assert(list.at(0) == 0);
    assert(list.at(1) == 1);
    assert(list.at(2) == 2);
    assert(list.at(3) == 3);
}