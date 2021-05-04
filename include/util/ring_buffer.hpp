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

#ifndef THAT_THIS_UTIL_RING_BUFFER_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_RING_BUFFER_HEADER_IS_ALREADY_INCLUDED

#ifndef UTIL_NOSTDLIB
#include <array>
#include <cstddef>
#include <iterator>
#include <stdexcept>
namespace util {
using std::array;
using std::out_of_range;
using std::ptrdiff_t;
using std::reverse_iterator;
using std::size_t;
}  // namespace util
#else
#include <util.hpp>
#endif  // UTIL_NOSTDLIB

namespace util {

namespace detail {
template <class T>
class ring_buffer_iterator;
template <class T>
class ring_buffer_const_iterator;
}  // namespace detail

/**
 * A fixed-size ring buffer implementation.
 */
template <class T, util::size_t N>
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
    ring_buffer(ring_buffer&&) noexcept = default;
    ring_buffer(const ring_buffer&) noexcept = default;
    auto operator=(ring_buffer&&) noexcept -> ring_buffer& = default;
    auto operator=(const ring_buffer&) noexcept -> ring_buffer& = default;

    constexpr auto at(size_type pos) -> reference;
    constexpr auto at(size_type pos) const -> const_reference;
    constexpr auto operator[](size_type pos) -> reference;
    constexpr auto operator[](size_type pos) const -> const_reference;
    constexpr auto front() -> reference;
    constexpr auto front() const -> const_reference;
    constexpr auto back() -> reference;
    constexpr auto back() const -> const_reference;
    constexpr auto data() noexcept -> pointer;
    constexpr auto data() const noexcept -> const_pointer;

    constexpr auto empty() const noexcept -> bool;
    constexpr auto size() const noexcept -> size_type;
    constexpr auto max_size() const noexcept -> size_type;

private:
    util::array<T, N> elements;
    util::size_t pos_ = 0;
    bool full_ = false;
};

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::at(size_type pos) -> ring_buffer<T, N>::reference {
    return elements.at(pos);
}

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::at(size_type pos) const -> ring_buffer<T, N>::const_reference {
    return elements.at(pos);
}

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::operator[](size_type pos) -> ring_buffer<T, N>::reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const ring_buffer<T, N>*>(this)->operator[](pos));
}

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::operator[](size_type pos) const
    -> ring_buffer<T, N>::const_reference {
    if (pos >= size()) {
        throw util::out_of_range{"pos is out of range"};
    }

    const auto abs_pos = (pos_ + pos) - N;
    return elements[abs_pos];
}

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::front() -> ring_buffer<T, N>::reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const ring_buffer<T, N>*>(this)->front());
}

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::front() const -> ring_buffer<T, N>::const_reference {
    if (full_ && pos_ < size() - 1) {
        return elements[pos_ + 1];
    }
    return elements[0];
}

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::back() -> ring_buffer<T, N>::reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const ring_buffer<T, N>*>(this)->back());
}

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::back() const -> ring_buffer<T, N>::const_reference {
    return elements[pos_];
}

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::data() noexcept -> ring_buffer<T, N>::pointer {
    return elements.data();
}

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::data() const noexcept -> ring_buffer<T, N>::const_pointer {
    return elements.data();
}

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::empty() const noexcept -> bool {
    return !full_ && pos_ != 0;
}

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::size() const noexcept -> ring_buffer<T, N>::size_type {
    return full_ ? N : pos_;
}

template <class T, util::size_t N>
constexpr auto ring_buffer<T, N>::max_size() const noexcept -> ring_buffer<T, N>::size_type {
    return elements.max_size();
}

}  // namespace util

#endif  // THAT_THIS_UTIL_RING_BUFFER_HEADER_IS_ALREADY_INCLUDED