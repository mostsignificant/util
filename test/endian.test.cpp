#include "gtest/gtest.h"
#include "util/endian.hpp"

#define assert EXPECT_TRUE

TEST(UtilEndian, HostToNetwork8bit) {
    //! [HostToNetwork8bit]
    assert(util::hton(uint8_t(127U)) == uint8_t(127U));
    //! [HostToNetwork8bit]

    EXPECT_EQ(util::hton(uint8_t(0U)), uint8_t(0U));
    EXPECT_EQ(util::hton(uint8_t(255U)), uint8_t(255U));

    EXPECT_EQ(util::hton(util::hton(uint16_t(127U))), uint16_t(127U));
}

TEST(UtilEndian, HostToNetwork16bit) {
    EXPECT_EQ(util::hton(uint16_t(0U)), uint16_t(0U));
    EXPECT_EQ(util::hton(uint16_t(4096U)), uint16_t(16));
    EXPECT_EQ(util::hton(uint16_t(65535U)), uint16_t(65535U));

    EXPECT_EQ(util::hton(util::hton(uint16_t(4096U))), uint16_t(4096U));
}

TEST(UtilEndian, HostToNetwork32bit) {
    EXPECT_EQ(util::hton(uint32_t(0U)), uint32_t(0U));
    EXPECT_EQ(util::hton(uint32_t(2147483648U)), uint32_t(128));
    EXPECT_EQ(util::hton(uint32_t(4294967296U)), uint32_t(4294967296U));

    EXPECT_EQ(util::hton(util::hton(uint32_t(2147483648U))),
              uint32_t(2147483648U));
}

TEST(UtilEndian, HostToNetwork64bit) {
    EXPECT_EQ(util::hton(uint64_t(0U)), uint64_t(0U));
    EXPECT_EQ(util::hton(uint64_t(9223372036854775807U)),
              uint64_t(18446744073709551487U));
    EXPECT_EQ(util::hton(uint64_t(18446744073709551615U)),
              uint64_t(18446744073709551615U));

    EXPECT_EQ(util::hton(util::hton(uint64_t(9223372036854775807U))),
              uint64_t(9223372036854775807U));
}

TEST(UtilEndian, NetworkToHost8bit) {
    EXPECT_EQ(util::ntoh(uint8_t(0U)), uint8_t(0U));
    EXPECT_EQ(util::ntoh(uint8_t(127U)), uint8_t(127U));
    EXPECT_EQ(util::ntoh(uint8_t(255U)), uint8_t(255U));

    EXPECT_EQ(util::ntoh(util::ntoh(uint16_t(127U))), uint16_t(127U));
}

TEST(UtilEndian, NetworkToHost16bit) {
    EXPECT_EQ(util::ntoh(uint16_t(0U)), uint16_t(0U));
    EXPECT_EQ(util::ntoh(uint16_t(16U)), uint16_t(4096U));
    EXPECT_EQ(util::ntoh(uint16_t(65535U)), uint16_t(65535U));

    EXPECT_EQ(util::ntoh(util::ntoh(uint16_t(4096U))), uint16_t(4096U));
}

TEST(UtilEndian, NetworkToHost32bit) {
    EXPECT_EQ(util::ntoh(uint32_t(0U)), uint32_t(0U));
    EXPECT_EQ(util::ntoh(uint32_t(128U)), uint32_t(2147483648U));
    EXPECT_EQ(util::ntoh(uint32_t(4294967296U)), uint32_t(4294967296U));

    EXPECT_EQ(util::ntoh(util::ntoh(uint32_t(2147483648U))),
              uint32_t(2147483648U));
}

TEST(UtilEndian, NetworkToHost64bit) {
    EXPECT_EQ(util::ntoh(uint64_t(0U)), uint64_t(0U));
    EXPECT_EQ(util::ntoh(uint64_t(18446744073709551487U)),
              uint64_t(9223372036854775807U));
    EXPECT_EQ(util::ntoh(uint64_t(18446744073709551615U)),
              uint64_t(18446744073709551615U));

    EXPECT_EQ(util::ntoh(util::ntoh(uint64_t(9223372036854775807U))),
              uint64_t(9223372036854775807U));
}