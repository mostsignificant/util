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

#ifndef THAT_THIS_UTIL_SCOPED_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_SCOPED_HEADER_IS_ALREADY_INCLUDED

namespace util {

/**
 * A class for managing heap memory within a certain scope.
 *
 * @code{.cpp}
 * util::scoped number(new int(100));
 * @endcode
 */
template <class T>
class scoped {
public:
    using element_type = T;
    using pointer = element_type*;
    using reference = element_type&;

    explicit scoped(pointer ptr = nullptr) noexcept;
    ~scoped();

    scoped(scoped&& other);
    scoped& operator=(scoped&& other);

    scoped(const scoped&) = delete;
    scoped& operator=(const scoped&) = delete;

    reference operator*() const;
    pointer operator->() const;
    explicit operator bool() const noexcept;

    pointer release() noexcept;
    void reset(pointer ptr) noexcept;
    void swap(scoped& other) noexcept;
    pointer get() const noexcept;

private:
    pointer ptr_ = nullptr;
};

template <class T>
scoped<T> make_scoped();

}  // namespace util

#if UTIL_ASSERT
#include <util.hpp>
#endif

/**
 * Constructs a scoped pointer from given memory.
 *
 * @
 */
template <class T>
util::scoped<T>::scoped(pointer ptr) noexcept : ptr_(ptr) {}

template <class T>
util::scoped<T>::~scoped() {
    if (ptr_) delete ptr_;
}

template <class T>
typename util::scoped<T>::reference util::scoped<T>::operator*() const {
#if defined UTIL_USE_EXCEPTIONS
    if (!ptr_) throw scoped_nullptr_exception();
#elif defined UTIL_USE_ASSERTIONS
    util::assert(ptr_);
#endif

    return *ptr_;
}

template <class T>
typename util::scoped<T>::pointer util::scoped<T>::operator->() const {
#if defined UTIL_USE_EXCEPTIONS
    if (!ptr_) throw scoped_nullptr_exception();
#elif defined UTIL_USE_ASSERTIONS
    util::assert(ptr_);
#endif

    return ptr_;
}

template <class T>
util::scoped<T>::operator bool() const noexcept {
    return ptr_ != nullptr;
}

template <class T>
typename util::scoped<T>::pointer util::scoped<T>::release() noexcept {
    const auto tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

template <class T>
void util::scoped<T>::reset(pointer ptr) noexcept {
    if (ptr_) delete ptr_;
    ptr_ = ptr;
}

template <class T>
void util::scoped<T>::swap(scoped& other) noexcept {
    const auto tmp = ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = tmp;
}

template <class T>
typename util::scoped<T>::pointer util::scoped<T>::get() const noexcept {
#if defined UTIL_USE_EXCEPTIONS
    if (!ptr_) throw scoped_nullptr_exception();
#elif defined UTIL_USE_ASSERTIONS
    util::assert(ptr_);
#endif

    return ptr_;
}

#endif  // THAT_THIS_UTIL_SCOPED_HEADER_IS_ALREADY_INCLUDED