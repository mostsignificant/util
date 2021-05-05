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

#ifndef THAT_THIS_UTIL_EXCEPTION_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_EXCEPTION_HEADER_IS_ALREADY_INCLUDED

#ifndef UTIL_NOSTDLIB
#include <exception>
#endif

namespace util {

#ifdef UTIL_NOSTDLIB
class exception {
#else
class exception : public std::exception {
#endif
public:
    explicit exception(const char* msg) : message(msg) {}

#ifdef UTIL_NOSTDLIB
    const char* what() const noexcept { return message; };
#else
    const char* what() const noexcept override { return message; };
#endif

private:
    const char* message;
};

}  // namespace util

#endif  // THAT_THIS_UTIL_EXCEPTION_HEADER_IS_ALREADY_INCLUDED