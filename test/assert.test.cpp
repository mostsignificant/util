#include "gtest/gtest.h"
#include "test.hpp"
#include "util/assert.hpp"

TEST(UtilAssert, Exception) {
    try {
        util_assert(false);
    } catch (const util::assertion& a) {
        assert(strcmp(a.what(), "assertion failed: false") == 0);
    }
}

TEST(UtilAssert, NoException) {
    util_assert(true);
    assert(true);
}
