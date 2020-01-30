#include "gtest/gtest.h"
#include "util/scoped.hpp"

namespace helper {
struct dtor_notifier {
    dtor_notifier(bool& ref) : ref(ref) {}
    ~dtor_notifier() { ref = true; }

    bool& ref;
};
}  // namespace helper

TEST(UtilScoped, Constructor) {
    const util::scoped number = new int(42);
    EXPECT_EQ(*number, 42);
}

TEST(UtilScoped, Destructor) {
    bool destroyed = false;

    { const util::scoped notifier = new helper::dtor_notifier(destroyed); }

    EXPECT_TRUE(destroyed);
}