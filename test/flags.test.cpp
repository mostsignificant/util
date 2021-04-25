#include "gtest/gtest.h"
#include "util/flags.hpp"

// clang-format off

TEST(UtilFlags, Ctor) {
//! [flags_ctor]
enum root_permissions_flag {
    read    = 0x04,
    write   = 0x02,
    execute = 0x01,
};
using root_permissions = util::flags<root_permissions_flag>;

const root_permissions rp{ read };
//! [flags_ctor]
}

// clang-format on