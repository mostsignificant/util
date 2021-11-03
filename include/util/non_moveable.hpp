// SPDX-FileCopyrightText: 2021 Christian Göhring <mostsig@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef THAT_THIS_UTIL_NON_COPYABLE_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_NON_COPYABLE_HEADER_IS_ALREADY_INCLUDED

namespace util {

/**
 * A helper class to make a class or struct non-moveable.
 *
 * This class can be derived from to make a class non-moveable in a verbose way.
 *
 * @snippet
 */
// NOLINTNEXTLINE
class non_moveable {
public:
    non_moveable(const non_moveable&&) = delete;
    auto operator=(const non_moveable&) -> non_moveable& = delete;
};

}  // namespace util

#endif  // THAT_THIS_UTIL_NON_COPYABLE_HEADER_IS_ALREADY_INCLUDED