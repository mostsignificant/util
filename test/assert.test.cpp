#include "gtest/gtest.h"
#include "test.hpp"
#include "util/assert.hpp"

TEST(UtilAssert, Exception) {
    try {
        util_assert(false);
    } catch (const util::assertion& a) {
        assert(a.what() == "assertion failed: false");
    }
}

TEST(UtilAssert, NoException) {
    util_assert(true);
    assert(true);
}