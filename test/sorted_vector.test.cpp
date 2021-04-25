#include <string>

#include "gtest/gtest.h"
#include "test.hpp"
#include "util/sorted_vector.hpp"

TEST(UtilSortedVector, CtorDefault) {
    //! [sorted_vector_ctor_default]
    util::sorted_vector<int> numbers;
    //! [sorted_vector_ctor_default]
}

TEST(UtilSortedVector, CtorAlloc) {
    //! [sorted_vector_ctor_alloc]
    util::sorted_vector<int> numbers({std::allocator<int>()});
    //! [sorted_vector_ctor_alloc]
}

TEST(UtilSortedVector, CtorCount) {
    //! [sorted_vector_ctor_count]
    util::sorted_vector<double> numbers(10, 1.0);
    assert(numbers.size() == 10);
    //! [sorted_vector_ctor_count]
}

TEST(UtilSortedVector, CtorIList) {
    //! [sorted_vector_ctor_ilist]
    const util::sorted_vector<int> numbers = {3, 1, 2};
    assert(numbers.at(0) == 1);
    assert(numbers.at(1) == 2);
    assert(numbers.at(2) == 3);
    //! [sorted_vector_ctor_ilist]
}

TEST(UtilSortedVector, Size) {
    //! [sorted_vector_size]
    util::sorted_vector<std::string> names;
    assert(names.size() == 0);
    names.insert("Chris");
    names.insert("Dora");
    assert(names.size() == 2);
    //! [sorted_vector_size]
}

TEST(UtilSortedVector, Capacity) {
    //! [sorted_vector_capacity]
    util::sorted_vector<std::string> cities;
    assert(cities.capacity() == 0);
    cities.insert("Madrid");
    cities.insert("Prague");
    cities.insert("Vienna");
    assert(cities.capacity() == 4);
    //! [sorted_vector_capacity]
}

TEST(UtilSortedVector, Clear) {
    //! [sorted_vector_clear]
    util::sorted_vector<double> doubles({1, 2, 3});
    const auto cap = doubles.capacity();
    doubles.clear();
    assert(doubles.size() == 0);
    assert(doubles.capacity() == cap);
    //! [sorted_vector_clear]
}