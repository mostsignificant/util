// SPDX-FileCopyrightText: 2021 Christian Göhring <mostsig@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef THAT_THIS_UTIL_ASSERT_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_ASSERT_HEADER_IS_ALREADY_INCLUDED

#include <util/exception.hpp>

namespace util {

/**
 * A helper exception when an assertion is not met.
 */
class assertion : public exception {
public:
    explicit assertion(const char* msg) : exception(msg) {}
};

}  // namespace util

#define util_assert(condition)                                  \
    if (!(condition)) {                                         \
        throw util::assertion{"assertion failed: " #condition}; \
    }

#endif  // THAT_THIS_UTIL_ASSERT_HEADER_IS_ALREADY_INCLUDED