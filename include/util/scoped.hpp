/*
 * util - a collection of utility classes and functions for C++
 * <https://github.com/sourcechris/util>
 *
 * MIT License
 *
 * Copyright (c) 2020 Christian Göhring
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

#pragma once

namespace util {

/**
 * A simple class for managing heap memory within a certain scope.
 *
 * @code{.cpp}
 * util::scoped number = new int(100);
 * @endcode
 */
template <class T>
class scoped {
public:
    explicit scoped(T* ptr) noexcept;
    ~scoped();

    constexpr scoped() noexcept = default;
    scoped(const scoped&)       = delete;
    scoped& operator=(const scoped&) = delete;

    T&       operator*() const;
    T*       operator->() const;
    explicit operator bool() const noexcept;

    T*   release() noexcept;
    void reset(T* ptr) noexcept;
    void swap(scoped& other) noexcept;
    T*   get() const noexcept;

private:
    T* ptr = nullptr;
};

#if defined(UTIL_USE_EXCEPTIONS)
class scoped_nullptr_exception {};
#endif

}  // namespace util

#if defined(UTIL_ASSERT)
#include "util/assert.hpp"
#endif

template <class T>
util::scoped<T>::scoped(T* ptr) noexcept : ptr(ptr) {}

template <class T>
util::scoped<T>::~scoped() {
    if (ptr) delete ptr;
}

template <class T>
T& util::scoped<T>::operator*() const {
#if defined(UTIL_USE_EXCEPTIONS)
    if (!ptr) throw scoped_nullptr_exception();
#elif defined(UTIL_ASSERT)
    util::assert(ptr);
#endif
    return *ptr;
}

template <class T>
T* util::scoped<T>::operator->() const {
#if defined(UTIL_USE_EXCEPTIONS)
    if (!ptr) throw scoped_nullptr_exception();
#endif
    return ptr;
}

template <class T>
util::scoped<T>::operator bool() const noexcept {
    return ptr != nullptr;
}

template <class T>
T* util::scoped<T>::release() noexcept {
    const auto tmp = ptr;
    ptr            = nullptr;
    return tmp;
}

template <class T>
void util::scoped<T>::reset(T* ptr) noexcept {
    if (this->ptr) delete this->ptr;
    this->ptr = ptr;
}

template <class T>
void util::scoped<T>::swap(scoped& other) noexcept {
    const auto tmp = ptr;
    ptr            = other.ptr;
    other.ptr      = tmp;
}

template <class T>
T* util::scoped<T>::get() const noexcept {
#if defined(UTIL_USE_EXCEPTIONS)
    if (!ptr) throw scoped_nullptr_exception();
#endif
    return ptr;
}