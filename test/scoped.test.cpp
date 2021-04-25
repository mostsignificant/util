#include "gtest/gtest.h"
#include "test.hpp"
#include "util/scoped.hpp"

namespace helper {
struct dtor_notifier {
    dtor_notifier(bool& ref) : ref(ref) {}
    ~dtor_notifier() { ref = true; }

    bool& ref;
};
}  // namespace helper

TEST(UtilScoped, CtorPointer) {
    // clang-format off
//! [scoped_ctor]
const util::scoped number(new int(42));
assert(number);
//! [scoped_ctor]
    // clang-format on
}

TEST(UtilScoped, CtorDefault) {
    const util::scoped<int> empty;
    assert(empty);
}

TEST(UtilScoped, Dtor) {
    bool destroyed = false;
    { const util::scoped notifier(new helper::dtor_notifier(destroyed)); }
    assert(destroyed);
}

TEST(UtilScoped, Deref) {
    const util::scoped six(new double(6.0));
    assert(*six == 6.0);
}
