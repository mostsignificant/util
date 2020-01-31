#include "gtest/gtest.h"
#include "util/scoped.hpp"

namespace helper {
struct dtor_notifier {
    dtor_notifier(bool& ref) : ref(ref) {}
    ~dtor_notifier() { ref = true; }

    bool& ref;
};
}  // namespace helper

TEST(UtilScoped, CtorPointer) {
    const util::scoped number(new int(42));
    EXPECT_TRUE(number);
}

TEST(UtilScoped, CtorDefault) {
    const util::scoped<int> empty;
    EXPECT_FALSE(empty);
}

TEST(UtilScoped, Dtor) {
    bool destroyed = false;

    { const util::scoped notifier(new helper::dtor_notifier(destroyed)); }

    EXPECT_TRUE(destroyed);
}

TEST(UtilScoped, Deref) {
    const util::scoped six(new double(6.0));
    EXPECT_EQ(*six, 6.0);
}
