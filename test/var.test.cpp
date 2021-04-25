#include "gtest/gtest.h"
#include "test.hpp"
#include "util/var.hpp"

TEST(UtilVar, CtorDefault) {
    //! [var_ctor_default]
    using height = util::var<unsigned long long>;
    height h;
    //! [var_ctor_default]
}