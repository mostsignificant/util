#include "gtest/gtest.h"
#include "util/non_moveable.hpp"

TEST(UtilNonMoveable, Derive) {
    class object : util::non_moveable {
        // ...
    };
    static_assert(!std::is_move_constructible<object>::value,
                  "object shall not be move constructible");

    assert(true);
}