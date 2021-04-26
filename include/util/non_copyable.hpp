/*
 * util - a collection of utility classes and functions for C++
 * <https://github.com/mostsignificant/util>
 *
 * MIT License
 *
 * Copyright (c) 2020-2021 Christian Göhring
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

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