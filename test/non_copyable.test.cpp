#include "gtest/gtest.h"
#include "util/non_copyable.hpp"

TEST(UtilNonMoveable, Derive) {
    class object : util::non_copyable {
        // ...
    };
    static_assert(!std::is_copy_constructible<object>::value,
                  "object shall not be copy constructible");

    assert(true);
}