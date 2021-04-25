/*
 * util - a collection of utility classes and functions for C++
 * <https://github.com/mostsignificant/util>
 *
 * MIT License
 *
 * Copyright (c) 2020 - 2021 Christian Göhring
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

#ifndef THAT_THIS_UTIL_RING_BUFFER_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_RING_BUFFER_HEADER_IS_ALREADY_INCLUDED

#ifndef UTIL_NO_STD_LIBRARY
#include <cstddef>
#include <iterator>
#include <stdexcept>
namespace util {
using std::out_of_range;
using std::ptrdiff_t;
using std::reverse_iterator;
using std::size_t;
}  // namespace util
#else
#include <util.hpp>
#endif  // UTIL_NO_STD_LIBRARY

namespace util {

namespace detail {
template <typename T>
class ring_buffer_iterator;
template <typename T>
class ring_buffer_const_iterator;
}  // namespace detail

template <typename T, util::size_t N>
class ring_buffer {
public:
    using value_type = T;
    using size_type = util::size_t;
    using difference_type = util::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = detail::ring_buffer_iterator<T>;
    using const_iterator = detail::ring_buffer_const_iterator<T>;
    using reverse_iterator = util::reverse_iterator<iterator>;
    using const_reverse_iterator = util::reverse_iterator<const_iterator>;

    ring_buffer() = default;
    ~ring_buffer() = default;
    ring_buffer(ring_buffer&&) = default;
    ring_buffer(const ring_buffer&) = default;
    ring_buffer& operator=(ring_buffer&&) = default;
    ring_buffer& operator=(const ring_buffer&) = default;

    constexpr reference at(size_type pos);
    constexpr const_reference at(size_type pos) const;
    constexpr reference operator[](size_type pos);
    constexpr const_reference operator[](size_type pos) const;
    constexpr reference front();
    constexpr const_reference front() const;
    constexpr reference back();
    constexpr const_reference back() const;
    constexpr pointer data() noexcept;
    constexpr const_pointer data() const noexcept;

    constexpr bool empty() const noexcept;
    constexpr size_type size() const noexcept;
    constexpr size_type max_size() const noexcept;

private:
    T elements_[N];
    util::size_t pos_ = 0;
    bool full_ = false;
};

template <typename T, util::size_t N>
constexpr typename ring_buffer<T, N>::reference ring_buffer<T, N>::at(
    size_type pos) {
    return const_cast<reference>(
        const_cast<const ring_buffer<T, N>*>(this)->at(pos));
}

template <typename T, util::size_t N>
constexpr typename ring_buffer<T, N>::const_reference ring_buffer<T, N>::at(
    size_type pos) const {
    if (!(pos < size())) throw util::out_of_range{"pos is out of range"};

    return elements_[pos];
}

template <typename T, util::size_t N>
constexpr typename ring_buffer<T, N>::reference ring_buffer<T, N>::operator[](
    size_type pos) {
    return const_cast<reference>(
        const_cast<const ring_buffer<T, N>*>(this)->operator[](pos));
}

template <typename T, util::size_t N>
constexpr typename ring_buffer<T, N>::const_reference
ring_buffer<T, N>::operator[](size_type pos) const {
    return elements_[pos];
}

template <typename T, util::size_t N>
constexpr typename ring_buffer<T, N>::reference ring_buffer<T, N>::front() {
    return const_cast<reference>(
        const_cast<const ring_buffer<T, N>*>(this)->front());
}

template <typename T, util::size_t N>
constexpr typename ring_buffer<T, N>::const_reference ring_buffer<T, N>::front()
    const {
    if (full_ && pos_ < size() - 1) return elements_[pos_ + 1];

    return elements_[0];
}

template <typename T, util::size_t N>
constexpr typename ring_buffer<T, N>::reference ring_buffer<T, N>::back() {
    return const_cast<reference>(
        const_cast<const ring_buffer<T, N>*>(this)->back());
}

template <typename T, util::size_t N>
constexpr typename ring_buffer<T, N>::const_reference ring_buffer<T, N>::back()
    const {
    return elements_[pos_];
}

template <typename T, util::size_t N>
constexpr typename ring_buffer<T, N>::pointer
ring_buffer<T, N>::data() noexcept {
    return const_cast<pointer>(
        const_cast<const ring_buffer<T, N>*>(this)->data());
}

template <typename T, util::size_t N>
constexpr typename ring_buffer<T, N>::const_pointer ring_buffer<T, N>::data()
    const noexcept {
    return &elements_[0];
}

template <typename T, util::size_t N>
constexpr bool ring_buffer<T, N>::empty() const noexcept {
    return !full_ && !pos_;
}

template <typename T, util::size_t N>
constexpr typename ring_buffer<T, N>::size_type ring_buffer<T, N>::size()
    const noexcept {
    return full_ ? N : pos_;
}

template <typename T, util::size_t N>
constexpr typename ring_buffer<T, N>::size_type ring_buffer<T, N>::max_size()
    const noexcept {
    return N;
}

}  // namespace util

#endif  // THAT_THIS_UTIL_RING_BUFFER_HEADER_IS_ALREADY_INCLUDED