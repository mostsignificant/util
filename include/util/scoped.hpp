// SPDX-FileCopyrightText: 2021 Christian Göhring <mostsig@gmail.com>
// SPDX-License-Identifier: MIT

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
    pointer get() const;

private:
    pointer ptr_ = nullptr;
};

}  // namespace util

#ifdef UTIL_ASSERT
#include "assert.hpp"
#endif

/**
 * Constructs a scoped pointer from a given memory block.
 */
template <class T>
util::scoped<T>::scoped(pointer ptr) noexcept : ptr_(ptr) {}

template <class T>
util::scoped<T>::~scoped() {
    if (ptr_) delete ptr_;
}

template <class T>
typename util::scoped<T>::reference util::scoped<T>::operator*() const {
#if defined UTIL_ASSERT
    util_assert(ptr_ != nullptr);
#endif

    return *ptr_;
}

template <class T>
typename util::scoped<T>::pointer util::scoped<T>::operator->() const {
#if defined UTIL_ASSERT
    util_assert(ptr_ != nullptr);
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
typename util::scoped<T>::pointer util::scoped<T>::get() const {
#if defined UTIL_ASSERT
    util_assert(ptr_ != nullptr);
#endif

    return ptr_;
}

#endif  // THAT_THIS_UTIL_SCOPED_HEADER_IS_ALREADY_INCLUDED