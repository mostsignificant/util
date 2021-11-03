// SPDX-FileCopyrightText: 2021 Christian Göhring <mostsig@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef THAT_THIS_UTIL_NON_COPYABLE_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_NON_COPYABLE_HEADER_IS_ALREADY_INCLUDED

namespace util {

/**
 * A helper class to make a class or struct non-copyable.
 *
 * This class can be derived from to make a class non-copyable in a verbose way.
 *
 * @snippet
 */
// NOLINTNEXTLINE
class non_copyable {
public:
    non_copyable(const non_copyable&) = delete;
    auto operator=(const non_copyable&) -> non_copyable& = delete;
};

}  // namespace util

#endif  // THAT_THIS_UTIL_NON_COPYABLE_HEADER_IS_ALREADY_INCLUDED