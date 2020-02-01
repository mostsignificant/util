#include "gtest/gtest.h"
#include "test.hpp"
#include "util/endian.hpp"

TEST(UtilEndian, HostToNetwork8bit) {
    //! [endian_hton_uint8t]
    assert(util::hton(uint8_t(127)) == uint8_t(127));
    //! [endian_hton_uint8t]

    EXPECT_EQ(util::hton(uint8_t(0)), uint8_t(0));
    EXPECT_EQ(util::hton(uint8_t(255)), uint8_t(255));
    EXPECT_EQ(util::hton(util::hton(uint16_t(127))), uint16_t(127));
}

TEST(UtilEndian, HostToNetwork16bit) {
    //! [endian_hton_uint16t]
    assert(util::hton(uint16_t(4096)) == uint16_t(16));
    //! [endian_hton_uint16t]

    EXPECT_EQ(util::hton(uint16_t(0)), uint16_t(0));
    EXPECT_EQ(util::hton(uint16_t(65535)), uint16_t(65535));
    EXPECT_EQ(util::hton(util::hton(uint16_t(4096))), uint16_t(4096));
}

TEST(UtilEndian, HostToNetwork32bit) {
    //! [endian_hton_uint32t]
    assert(util::hton(uint32_t(2147483648)) == uint32_t(128));
    //! [endian_hton_uint32t]

    EXPECT_EQ(util::hton(uint32_t(0)), uint32_t(0));
    EXPECT_EQ(util::hton(uint32_t(4294967296)), uint32_t(4294967296));
    EXPECT_EQ(util::hton(util::hton(uint32_t(2147483648))),
              uint32_t(2147483648));
}

TEST(UtilEndian, HostToNetwork64bit) {
    //! [endian_hton_uint64t]
    assert(util::hton(uint64_t(9223372036854775807U)) ==
           uint64_t(18446744073709551487U));
    //! [endian_hton_uint64t]

    EXPECT_EQ(util::hton(uint64_t(0)), uint64_t(0));
    EXPECT_EQ(util::hton(uint64_t(18446744073709551615U)),
              uint64_t(18446744073709551615U));
    EXPECT_EQ(util::hton(util::hton(uint64_t(9223372036854775807))),
              uint64_t(9223372036854775807));
}

TEST(UtilEndian, NetworkToHost8bit) {
    EXPECT_EQ(util::ntoh(uint8_t(0)), uint8_t(0));
    EXPECT_EQ(util::ntoh(uint8_t(127)), uint8_t(127));
    EXPECT_EQ(util::ntoh(uint8_t(255)), uint8_t(255));

    EXPECT_EQ(util::ntoh(util::ntoh(uint16_t(127))), uint16_t(127));
}

TEST(UtilEndian, NetworkToHost16bit) {
    EXPECT_EQ(util::ntoh(uint16_t(0)), uint16_t(0));
    EXPECT_EQ(util::ntoh(uint16_t(16)), uint16_t(4096));
    EXPECT_EQ(util::ntoh(uint16_t(65535)), uint16_t(65535));

    EXPECT_EQ(util::ntoh(util::ntoh(uint16_t(4096))), uint16_t(4096));
}

TEST(UtilEndian, NetworkToHost32bit) {
    EXPECT_EQ(util::ntoh(uint32_t(0)), uint32_t(0));
    EXPECT_EQ(util::ntoh(uint32_t(128)), uint32_t(2147483648));
    EXPECT_EQ(util::ntoh(uint32_t(4294967296)), uint32_t(4294967296));

    EXPECT_EQ(util::ntoh(util::ntoh(uint32_t(2147483648))),
              uint32_t(2147483648));
}

TEST(UtilEndian, NetworkToHost64bit) {
    EXPECT_EQ(util::ntoh(uint64_t(0)), uint64_t(0));
    EXPECT_EQ(util::ntoh(uint64_t(18446744073709551487U)),
              uint64_t(9223372036854775807U));
    EXPECT_EQ(util::ntoh(uint64_t(18446744073709551615U)),
              uint64_t(18446744073709551615U));

    EXPECT_EQ(util::ntoh(util::ntoh(uint64_t(9223372036854775807U))),
              uint64_t(9223372036854775807U));
}