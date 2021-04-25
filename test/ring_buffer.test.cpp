#include "gtest/gtest.h"
#include "util/ring_buffer.hpp"

TEST(UtilRingBuffer, Ctor) {
    //! [ring_buffer_ctor]
    util::ring_buffer<int, 24> values;
    //! [ring_buffer_ctor]
}