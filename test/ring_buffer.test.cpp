#include "gtest/gtest.h"
#include "test.hpp"
#include "util/ring_buffer.hpp"

TEST(UtilRingBuffer, Ctor) {
    //! [ring_buffer_ctor]
    util::ring_buffer<int, 24> values;
    //! [ring_buffer_ctor]
}

TEST(UtilRingBuffer, CtorIlist) {
    //! [ring_buffer_ctor_ilist]
    util::ring_buffer<int, 5> values = {1, 2, 3, 4, 5};
    //! [ring_buffer_ctor_ilist]
}

TEST(UtilRingBuffer, At) {
    //! [ring_buffer_at]
    util::ring_buffer<int, 5> values = {1, 2, 3, 4, 5};
    assert(values.at(0) == 1);
    assert(values.at(4) == 5);
    //! [ring_buffer_at]

    try {
        auto&& x = values.at(5);
    } catch (const std::out_of_range& oor) {
        ASSERT_TRUE(true);
    }

    util::ring_buffer<int, 5> overflow = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(overflow.at(0), 2);
    EXPECT_EQ(overflow.at(4), 6);
}

TEST(UtilRingBuffer, AtConst) {
    //! [ring_buffer_at_const]
    const util::ring_buffer<int, 5> values = {1, 2, 3, 4, 5};
    assert(values.at(0) == 1);
    assert(values.at(4) == 5);
    //! [ring_buffer_at_const]

    try {
        auto&& x = values.at(5);
    } catch (const std::out_of_range& oor) {
        ASSERT_TRUE(true);
    }

    const util::ring_buffer<int, 5> overflow = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(overflow.at(0), 2);
    EXPECT_EQ(overflow.at(4), 6);
}

TEST(UtilRingBuffer, PushFront) {
    //! [ring_buffer_push_front]
    util::ring_buffer<int, 5> values = {1, 2, 3, 4, 5};
    values.push_front(6);
    assert(values.at(0) == 6);
    assert(values.at(4) == 4);
    //! [ring_buffer_push_front]
}

TEST(UtilRingBuffer, PushBack) {
    //! [ring_buffer_push_back]
    util::ring_buffer<int, 5> values = {1, 2, 3, 4, 5};
    values.push_back(6);
    assert(values.at(0) == 2);
    assert(values.at(4) == 6);
    //! [ring_buffer_push_back]
}